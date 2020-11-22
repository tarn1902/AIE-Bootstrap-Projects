/*----------------------------------------
File Name: main.h
Purpose: Runs Server
Author: Tarn Cooper
Modified: 18 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include <iostream>
#include <BitStream.h>
#include <GameMessages.h>
#include <RakPeerInterface.h>

//Prototype functions
void StartUp();
void SendNewClientID(RakNet::RakPeerInterface* pPeerInterface, RakNet::SystemAddress& address);
void HandleNetworkMessages(RakNet::RakPeerInterface* pPeerInterface);

int nextClientID = 1;
const unsigned short PORT = 5456;

//-----------------------------------------------------------
// Main function
// return (int): Returns int depending on results of program
//-----------------------------------------------------------
int main()
{
	StartUp();
	return 0;
}

//-----------------------------------------------------------
// Starts up server
//-----------------------------------------------------------
void StartUp()
{
	//Message for starting up server
	std::cout << "Starting up the server..." << std::endl;
	//Inititalse interface
	RakNet::RakPeerInterface* pPeerInterface = RakNet::RakPeerInterface::GetInstance();

	//Create Socket descriptor
	RakNet::SocketDescriptor sd(PORT, 0);

	//Starts up with max 32 connection on port
	pPeerInterface->Startup(32, &sd, 1);
	pPeerInterface->SetMaximumIncomingConnections(32);

	HandleNetworkMessages(pPeerInterface);
}

//-----------------------------------------------------------
// Sends Id of new client connected
// pPeerInterface (RakNet::RakPeerInterface*): What is the 
//  interface?
// address (RakNet::SystemAddress&): Where will message be 
//  sent?
//-----------------------------------------------------------
void SendNewClientID(RakNet::RakPeerInterface* pPeerInterface,  RakNet::SystemAddress& address)
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)GameMessages::ID_SERVER_SET_CLIENT_ID);
	bs.Write(nextClientID);
	nextClientID++;
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED,
		0, address, false);
}

//-----------------------------------------------------------
// Handles messages sent by clients
// pPeerInterface (RakNet::RakPeerInterface*): What is the 
//  interface?
//-----------------------------------------------------------
void HandleNetworkMessages(RakNet::RakPeerInterface* pPeerInterface)
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
				SendNewClientID(pPeerInterface, packet->systemAddress);
				break;
			}
			case ID_REMOTE_DISCONNECTION_NOTIFICATION:
			{
				std::cout << "A client has disconnected.\n";
				RakNet::BitStream bsIn(packet->data, packet->length, false);
				bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
				int clientID;
				bsIn.Read(clientID);

				RakNet::BitStream bs;
				bs.Write((RakNet::MessageID)ID_REMOTE_DISCONNECTION_NOTIFICATION);
				bs.Write(clientID);
				pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, true);

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
				break;
			}
			case ID_CLIENT_UPDATE_DATA:
			{
				RakNet::BitStream bs(packet->data, packet->length, false);
				pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, true);
				break;
			}
			case ID_CLIENT_CLIENT_DATA_X:
			{
				RakNet::BitStream bs(packet->data, packet->length, false);
				pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, true);
				break;
			}
			case ID_CLIENT_CLIENT_DATA_Y:
			{
				RakNet::BitStream bs(packet->data, packet->length, false);
				pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, true);
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



