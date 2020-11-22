/*----------------------------------------
File Name: Client.cpp
Purpose: Functions for client class.
Author: Tarn Cooper
Modified: 25 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Client.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "GameMessages.h"
#include <BitStream.h>
#include <MessageIdentifiers.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

//-----------------------------------------------------------
// Constructs client
//-----------------------------------------------------------
Client::Client() {

}

//-----------------------------------------------------------
// Destructs client
//-----------------------------------------------------------
Client::~Client() {
}

//-----------------------------------------------------------
// Starts up client with setting data
//-----------------------------------------------------------
bool Client::startup() {
	HandleNetworkConnection();
	setBackgroundColour(0.25f, 0.25f, 0.25f);
	myGameObject.data.position = glm::vec3(0);
	myGameObject.data.colour = glm::vec4(1, 0, 0, 1);
	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(0, 10, 10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(),
		0.1f, 1000.f);

	return true;
}

//-----------------------------------------------------------
// Shuts down client
//-----------------------------------------------------------
void Client::shutdown() {

	Gizmos::destroy();
}

//-----------------------------------------------------------
// Updates client with inputs and data that is changed each 
//  frame
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
void Client::update(float deltaTime) {

	HandleNetworkMessages();
	// query time since application started
	float time = getTime();

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		myGameObject.data.position.x -= 10.0f * deltaTime;
		facing = glm::vec3(-1, 0, 0);
		SendClientGameObject();
		
	}
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		myGameObject.data.position.x += 10.0f * deltaTime;
		facing = glm::vec3(1, 0, 0);
		SendClientGameObject();
	}
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		myGameObject.data.position.z -= 10.0f * deltaTime;
		facing = glm::vec3(0, 0, -1);
		SendClientGameObject();

	}
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		myGameObject.data.position.z += 10.0f * deltaTime;
		facing = glm::vec3(0, 0, 1);
		SendClientGameObject();
	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
	{
		myGameObject.data.position.y += 10.0f * deltaTime;
		facing = glm::vec3(0, 1, 0);
		SendClientGameObject();

	}
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_CONTROL))
	{
		myGameObject.data.position.y -= 10.0f * deltaTime;
		facing = glm::vec3(0, -1, 0);
		SendClientGameObject();
	}
	bool keyDown = input->isKeyDown(aie::INPUT_KEY_SPACE);
	if (!wasKeyDown && keyDown)
	{
		this->SendSpawnBulletPacket();
	}
	wasKeyDown = keyDown;
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	
}

//-----------------------------------------------------------
// Draws images on screen
//-----------------------------------------------------------
void Client::draw() {

	// wipe the screen to the background colour
	clearScreen();
	Gizmos::addSphere(myGameObject.data.position, 1.0f, 32, 32, myGameObject.data.colour);
	Gizmos::addSphere(myGameObject.data.position + glm::vec3(facing.x * 0.7, facing.y * 0.7, facing.z * 0.7), 0.5f, 12, 12, glm::vec4(1));
	Gizmos::addSphere(myGameObject.data.position + glm::vec3(facing.x * 1.0, facing.y * 1.0, facing.z * 1.0), 0.25f, 6, 6, glm::vec4(0, 0, 0, 1));
	for (auto& otherClient : otherClientGameObjects)
	{
		if (otherClient.first >= 1000)
		{
			Gizmos::addSphere(otherClient.second.data.position, 0.2f, 8, 8, otherClient.second.data.colour);
		}
		else
		{
			Gizmos::addSphere(otherClient.second.data.position, 1.0f, 32, 32, otherClient.second.data.colour);
		}
		
	}
	// update perspective in case window resized
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
		getWindowWidth() / (float)getWindowHeight(),
		0.1f, 1000.f);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}


//-----------------------------------------------------------
// Creates instance of RakPeer interface
//-----------------------------------------------------------
void Client::HandleNetworkConnection()
{
	pPeerInterface = RakNet::RakPeerInterface::GetInstance();
	InitialiseClientConnection();
}

//-----------------------------------------------------------
// Connects interface to specfic server
//-----------------------------------------------------------
void Client::InitialiseClientConnection()
{
	RakNet::SocketDescriptor sd;
	pPeerInterface->Startup(1, &sd, 1);

	std::cout << "Connecting to server at: " << IP << std::endl;

	RakNet::ConnectionAttemptResult res = pPeerInterface->Connect(IP, PORT, nullptr, 0);

	if (res != RakNet::CONNECTION_ATTEMPT_STARTED)
	{
		std::cout << "Unable to start connection, Error number: " << res << std::endl;
	}
}

//-----------------------------------------------------------
// Handles messages sent by server
//-----------------------------------------------------------
void Client::HandleNetworkMessages()
{
	RakNet::Packet* packet;

	for (packet = pPeerInterface->Receive(); packet; pPeerInterface->DeallocatePacket(packet), packet = pPeerInterface->Receive())
	{
		switch (packet->data[0])
		{
		case ID_SERVER_TEXT_MESSAGE:
		{
			RakNet::BitStream bsIn(packet->data, packet->length, false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			RakNet::RakString str;
			bsIn.Read(str);
			std::cout << str.C_String() << std::endl;
			break;
		}
		case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			std::cout << "Another client has disconnected.\n";
			break;
		case ID_REMOTE_CONNECTION_LOST:
			std::cout << "Another client has lost the connection.\n";
			break;
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
			std::cout << "Another client has connected.\n";
			break;
		case ID_CONNECTION_REQUEST_ACCEPTED:
			std::cout << "Our connection request has been accepted.\n";
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			std::cout << "The server is full.\n";
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			std::cout << "We have been disconnected.\n";
			break;
		case ID_CONNECTION_LOST:
			std::cout << "Connection lost.\n";
			break;
		case ID_SERVER_SET_CLIENT_ID:
			OnSetClientIDPacket(packet);
			break;
		case ID_CLIENT_CLIENT_DATA:
			OnRecievedClientDataPacket(packet);
			break;
		case ID_SERVER_DESPAWN:
			OnDespawn(packet);
			break;
		case ID_SERVER_POINT:
			OnRecievedPoints(packet);
			system("cls");
			std::cout << "You: Score:" << myGameObject.points << std::endl;
			for (unsigned int i = 1; i < otherClientGameObjects.size() + 1; ++i)
			{
				if (myGameObject.id != i)
				{
					std::cout << "Player "<< otherClientGameObjects[i].id << ": Score:" << otherClientGameObjects[i].points << std::endl;
				}
			}
			break;
		default:
			std::cout << "Received a message with a unknown id: " << packet->data[0];
			break;
	}
	}
}

//-----------------------------------------------------------
// Handles message of type ID_SERVER_SET_CLIENT_ID
// packet (RakNet::Packet*): What was packet caught?
//-----------------------------------------------------------
void Client::OnSetClientIDPacket(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	bsIn.Read(myGameObject.id);
	myGameObject.data.colour = GameObject::GetColour(myGameObject.id);
	std::cout << "Set my client ID to: " << myGameObject.id << std::endl;
}

//-----------------------------------------------------------
// Responds to input changes
//-----------------------------------------------------------
void Client::SendClientGameObject()
{
	myGameObject.Write(pPeerInterface, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

//-----------------------------------------------------------
// Handles message of type ID_CLIENT_CLIENT_DATA
// packet (RakNet::Packet*): What was packet caught?
//-----------------------------------------------------------
void Client::OnRecievedClientDataPacket(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	int clientID;
	bsIn.Read(clientID);
	//If the clientID does not match our ID, we need to update
	//our client GameObject information.
	if (clientID != myGameObject.id)
	{
		GameObject clientData;
		clientData.Read(packet);
		otherClientGameObjects[clientID] = clientData;
	}
}

//-----------------------------------------------------------
// Sends message to server to handle new bullet
//-----------------------------------------------------------
void Client::SendSpawnBulletPacket()
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)GameMessages::ID_CLIENT_SPAWN_BULLET);

	glm::vec3 spawnPos = myGameObject.data.position + facing * 1.5f;

	bs.Write((char*)& spawnPos, sizeof(glm::vec3));
	bs.Write((char*)& facing, sizeof(glm::vec3));
	bs.Write(myGameObject.id);
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

//-----------------------------------------------------------
// Handles message of ID_SERVER_DESPAWN
// packet (RakNet::Packet*): What was packet caught?
//-----------------------------------------------------------
void Client::OnDespawn(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	int id;
	bsIn.Read(id);
	otherClientGameObjects.erase(id);
}

//-----------------------------------------------------------
// Handles message of ID_SERVER_POINT
// packet (RakNet::Packet*): What was packet caught?
//-----------------------------------------------------------
void Client::OnRecievedPoints(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	int pointID;
	bsIn.Read(pointID);
	if (pointID == myGameObject.id)
	{
		myGameObject.points++;
	}
	else
	{
		otherClientGameObjects[pointID].points++;
	}
}