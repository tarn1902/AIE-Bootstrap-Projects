/*----------------------------------------
File Name: Server.cpp
Purpose: Function of server class
Author: Tarn Cooper
Modified: 25 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Server.h"
#include <iostream>
#include <BitStream.h>
#include <GameMessages.h>
#include <thread>
#include <vector>
const unsigned short PORT = 5456;

//-----------------------------------------------------------
// Starts up server
//-----------------------------------------------------------
void Server::StartUp()
{
	//Message for starting up server
	std::cout << "Starting up the server..." << std::endl;
	//Inititalse interface
	pPeerInterface = RakNet::RakPeerInterface::GetInstance();

	//Create Socket descriptor
	RakNet::SocketDescriptor sd(PORT, 0);

	//std::thread pingThread(SendClientPing, pPeerInterface);
	//Starts up with max 32 connection on port
	pPeerInterface->Startup(32, &sd, 1);
	pPeerInterface->SetMaximumIncomingConnections(32);

	std::thread updateThread(UpdateThread, this, pPeerInterface);
	HandleNetworkMessages();
}

//-----------------------------------------------------------
// Sends new client id to client on request
// address (RakNet::SystemAddress&): Where will packet be 
//  sent?
//-----------------------------------------------------------
void Server::SendNewClientID(RakNet::SystemAddress& address)
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)GameMessages::ID_SERVER_SET_CLIENT_ID);
	bs.Write(nextClientID);
	nextClientID++;
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, address, false);

	for (auto it = gameObjects.begin(); it != gameObjects.end(); it++)
	{
		GameObject obj = it->second;
		obj.Write(pPeerInterface, address, false);
	}

	int id = nextClientID - 1;
	GameObject obj;
	obj.data.position = glm::vec3(0);
	obj.data.colour = GameObject::GetColour(id);
	obj.id = id;
	obj.Write(pPeerInterface, address, true);
}

//-----------------------------------------------------------
// Handles any package from clients
//-----------------------------------------------------------
void Server::HandleNetworkMessages()
{
	RakNet::Packet* packet = nullptr;
	while (true)
	{
		for (packet = pPeerInterface->Receive(); packet; pPeerInterface->DeallocatePacket(packet), packet = pPeerInterface->Receive())
		{
			switch (packet->data[0])
			{
			case ID_NEW_INCOMING_CONNECTION:
			{
				std::cout << "A connection is incoming.\n";
				SendNewClientID(packet->systemAddress);
				break;
			}
			case ID_DISCONNECTION_NOTIFICATION:
			{
				std::cout << "A client has disconnected.\n";
				break;
			}
			case ID_CONNECTION_LOST:
			{
				std::cout << "A client lost the connection.\n";
				break;
			}
			case ID_CLIENT_CLIENT_DATA:
			{
				RakNet::BitStream bs(packet->data, packet->length, false);
				pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, true);
				// read the packet and store in our list
				GameObject clientData;
				clientData.Read(packet);
				gameObjects[clientData.id] = clientData;
				break;
			}
			case ID_CLIENT_SPAWN_BULLET:
			{
				OnSpawnBullet(packet);
				break;
			}

			default:
			{
				std::cout << "Received a message with a unknown id: " << packet->data[0] << std::endl;
				break;
			}
			}
		}
	}
}

//-----------------------------------------------------------
// Handles message of spawning a bullet
// packet (RakNet::Packet*): What is the packet?
//-----------------------------------------------------------
void Server::OnSpawnBullet(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	glm::vec3 pos;
	glm::vec3 vel;
	int parentID;
	bsIn.Read((char*)& pos, sizeof(glm::vec3));
	bsIn.Read((char*)& vel, sizeof(glm::vec3));
	bsIn.Read(parentID);
	SpawnObject(pos, vel, parentID);
	gameObjects[nextServerID - 1].lifetime = 5.0f;

}

//-----------------------------------------------------------
// Creates new gameobject
// position (glm::vec3): Where will this object spawn?
// velocity (glm::vec3): Where will this object be heading?
// parentID (int): Who spawned it?
//-----------------------------------------------------------
void Server::SpawnObject(glm::vec3 position, glm::vec3 velocity, int parentID)
{
	gameObjects[nextServerID] = GameObject();
	gameObjects[nextServerID].id = nextServerID;
	gameObjects[nextServerID].data.position = position;
	gameObjects[nextServerID].data.velocity = velocity;
	gameObjects[nextServerID].parentId = parentID;
	nextServerID++;
}

//-----------------------------------------------------------
// Updates gameobjects on diffrent thread
// server (Server*): What server will this thread work with?
// pPeerInterface (RakNet::RakPeerInterface*): What will be 
//  the interface?
//-----------------------------------------------------------
void Server::UpdateThread(Server* server, RakNet::RakPeerInterface* pPeerInterface)
{
	const int deltaTime = 17; // time in milliseconds per broadcast
	while (true)
	{
		std::vector<int> deathRow;
		for (auto it = server->gameObjects.begin(); it != server->gameObjects.end(); it++)
		{
			GameObject& obj = it->second; // broadcast to every client if we're server controlled
			if (obj.id >= 1000)
			{
				obj.Update(deltaTime * 0.001f);
				obj.Write(pPeerInterface, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
				obj.lifetime -= deltaTime * 0.001f;
				// if expired, store for now in this list rather than erasing while iterating
				if (obj.lifetime <= 0)
				{
					deathRow.push_back(obj.id);
				}
				for (auto it2 = server->gameObjects.begin(); it2 != server->gameObjects.end(); it2++)
				{
					GameObject& obj2 = it2->second; // broadcast to every client if we're server controlled
					if (obj2.id < 1000)
					{
						if (obj2.id != obj.parentId)
						{
							if (glm::distance(obj2.data.position, obj.data.position) < 1.2f)
							{
								deathRow.push_back(obj.id);
								server->SendScores(obj.parentId);
							}
						}
					}
				}
			}
		}
		// remove expired objects from our map of gameobjects
		for (int i = 0; i < deathRow.size(); i++)
		{
			server->Despawn(deathRow[i]);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(deltaTime));
	}
}

//-----------------------------------------------------------
// Despawns object with id
// id (int): What is the id of object?
//-----------------------------------------------------------
void Server::Despawn(int id)
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)GameMessages::ID_SERVER_DESPAWN);
	bs.Write(id);
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
		RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	// erase from our local list
	gameObjects.erase(id);

}

//-----------------------------------------------------------
// Send increased score for this id
// id (int): What is the id of object?
//-----------------------------------------------------------
void Server::SendScores(int id)
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)GameMessages::ID_SERVER_POINT);
	bs.Write(id);
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

}
