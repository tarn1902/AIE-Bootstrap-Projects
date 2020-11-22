/*----------------------------------------
File Name: Client.cpp
Purpose: Functions for client class.
Author: Tarn Cooper
Modified: 18 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Client.h"
#include "Gizmos.h"
#include "Input.h"
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
	myGameObject.position = glm::vec3(0);
	myGameObject.colour = glm::vec4(1, 0, 0, 1);
	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(0, 0, 10), vec3(0), vec3(0, 1, 0));
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
		myGameObject.position.x -= 10.0f * deltaTime;
		SendXCoordinates();
	}
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		myGameObject.position.x += 10.0f * deltaTime;
		SendXCoordinates();
	}

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		myGameObject.position.y -= 10.0f * deltaTime;
		SendXCoordinates();
	}
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
		myGameObject.position.y += 10.0f * deltaTime;
		SendXCoordinates();
	}

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		SendDisconnect();
		quit();
	}
		
}

//-----------------------------------------------------------
// Draws images on screen
//-----------------------------------------------------------
void Client::draw() {

	// wipe the screen to the background colour
	clearScreen();
	Gizmos::addSphere(myGameObject.position, 1.0f, 32, 32, myGameObject.colour);
	for (auto& otherClient : otherClientGameObjects)
	{
		Gizmos::addSphere(otherClient.second.position, 1.0f, 32, 32, otherClient.second.colour);
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
		{
			std::cout << "Another client has disconnected.\n";
			RakNet::BitStream bsIn(packet->data, packet->length, false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			int clientID;
			bsIn.Read(clientID);
			otherClientGameObjects.erase(clientID);
			break;
		}
		case ID_REMOTE_CONNECTION_LOST:
		{
			std::cout << "Another client has lost the connection.\n";
			break;
		}
		case ID_REMOTE_NEW_INCOMING_CONNECTION:
		{
			std::cout << "Another client has connected.\n";
			break;
		}
		case ID_CONNECTION_REQUEST_ACCEPTED:
		{
			std::cout << "Our connection request has been accepted.\n";
			break;
		}
		case ID_NO_FREE_INCOMING_CONNECTIONS:
		{
			std::cout << "The server is full.\n";
			break;
		}
		case ID_DISCONNECTION_NOTIFICATION:
		{
			std::cout << "We have been disconnected.\n";
			break;
		}
		case ID_CONNECTION_LOST:
		{
			std::cout << "Connection lost.\n";
			break;
		}
		case ID_SERVER_SET_CLIENT_ID:
		{
			OnSetClientIDPacket(packet);
			break;
		}
		case ID_CLIENT_CLIENT_DATA:
		{
			OnReceivedClientDataPacket(packet);
			break;
		}
		case ID_CLIENT_UPDATE_DATA:
		{
			
			OnReceivedClientDataPacketUpdate(packet);
			break;
		}
		case ID_CLIENT_CLIENT_DATA_X:
		{
			OnReceivedClientDataPacketX(packet);
			break;
		}
		case ID_CLIENT_CLIENT_DATA_Y:
		{
			OnReceivedClientDataPacketY(packet);
			break;
		}
		default:
		{
			std::cout << "Received a message with a unknown id: " << packet->data[0];
			break;
		}
		}
	}
}

//-----------------------------------------------------------
// Handles message of type ID_CLIENT_CLIENT_DATA
// packet (RakNet::Packet*): What was packet caught?
//-----------------------------------------------------------
void Client::OnReceivedClientDataPacket(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	int clientID;
	bsIn.Read(clientID);
	//If the clientID does not match our ID, we need to update
	//our client GameObject information.
	if (clientID != myClientID)
	{
		GameObject clientData;
		bsIn.Read((char*)& clientData, sizeof(GameObject));
		otherClientGameObjects[clientID] = clientData;
		//For now, just output the Game Object information to the
		//console
		std::cout << "Client " << clientID <<
			" at: " << clientData.position.x <<
			" " << clientData.position.z << std::endl;
	}
}

//-----------------------------------------------------------
// Handles message of type ID_CLIENT_UPDATE_DATA
// packet (RakNet::Packet*): What was packet caught?
//-----------------------------------------------------------
void Client::OnReceivedClientDataPacketUpdate(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	int clientID;
	bsIn.Read(clientID);
	//If the clientID does not match our ID, we need to update
	//our client GameObject information.
	if (clientID != myClientID)
	{
		GameObject clientData;
		bsIn.Read((char*)& clientData, sizeof(GameObject));
		otherClientGameObjects[clientID] = clientData;
		//For now, just output the Game Object information to the
		//console
		std::cout << "Client " << clientID <<
			" at: " << clientData.position.x <<
			" " << clientData.position.z << std::endl;
	}

	//Responds with updating new client
	SendClientGameObject();
}

//-----------------------------------------------------------
// Handles message of type ID_CLIENT_CLIENT_DATA_X
// packet (RakNet::Packet*): What was packet caught?
//-----------------------------------------------------------
void Client::OnReceivedClientDataPacketX(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	int clientID;
	bsIn.Read(clientID);
	//If the clientID does not match our ID, we need to update
	//our client GameObject information.
	if (clientID != myClientID)
	{
		float clientDataX;
		bsIn.Read((char*)& clientDataX, sizeof(float));
		otherClientGameObjects[clientID].position.x = clientDataX;
	}

}

//-----------------------------------------------------------
// Sends message if x coordinates change
//-----------------------------------------------------------
void Client::SendXCoordinates()
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)GameMessages::ID_CLIENT_CLIENT_DATA_X);
	bs.Write(myClientID);
	bs.Write((char*)& myGameObject.position.x, sizeof(float));
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

//-----------------------------------------------------------
// Handles message of type ID_CLIENT_CLIENT_DATA_Y
// packet (RakNet::Packet*): What was packet caught?
//-----------------------------------------------------------
void Client::OnReceivedClientDataPacketY(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	int clientID;
	bsIn.Read(clientID);
	//If the clientID does not match our ID, we need to update
	//our client GameObject information.
	if (clientID != myClientID)
	{
		float clientDataY;
		bsIn.Read((char*)& clientDataY, sizeof(float));
		otherClientGameObjects[clientID].position.y = clientDataY;
	}

}

//-----------------------------------------------------------
// Sends message if y coordinates change
//-----------------------------------------------------------
void Client::SendYCoordinates()
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)GameMessages::ID_CLIENT_CLIENT_DATA_Y);
	bs.Write(myClientID);
	bs.Write((char*)& myGameObject.position.y, sizeof(float));
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

//-----------------------------------------------------------
// Responds to message of type ID_CLIENT_UPDATE_DATA
//-----------------------------------------------------------
void Client::SendClientGameObject()
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)GameMessages::ID_CLIENT_CLIENT_DATA);
	bs.Write(myClientID);
	bs.Write((char*)& myGameObject, sizeof(GameObject));
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

//-----------------------------------------------------------
// Sends message to other clients when started
//-----------------------------------------------------------
void Client::SendClientGameObjectStart()
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)GameMessages::ID_CLIENT_UPDATE_DATA);
	bs.Write(myClientID);
	bs.Write((char*)& myGameObject, sizeof(GameObject));
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

//-----------------------------------------------------------
// Sends message to other clients when this client closes
//-----------------------------------------------------------
void Client::SendDisconnect()
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)ID_REMOTE_DISCONNECTION_NOTIFICATION);
	bs.Write(myClientID);
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

//-----------------------------------------------------------
// Handles message of type ID_SERVER_SET_CLIENT_ID
// packet (RakNet::Packet*): What was packet caught?
//-----------------------------------------------------------
void Client::OnSetClientIDPacket(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	bsIn.Read(myClientID);
	std::cout << "Set my client ID to: " << myClientID << std::endl;
	//Updates other clients
	SendClientGameObjectStart();
}

