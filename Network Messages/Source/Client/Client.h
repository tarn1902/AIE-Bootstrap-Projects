/*----------------------------------------
File Name: Client.h
Purpose: Makes client game for server
Author: Tarn Cooper
Modified: 18 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Application.h"
#include <glm/mat4x4.hpp>
#include <RakPeerInterface.h>
#include <GameObject.h>
#include <GameMessages.h>
#include <unordered_map>

//Class for client
class Client : public aie::Application {
public:

	Client();
	virtual ~Client();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void HandleNetworkConnection();
	void InitialiseClientConnection();
	void HandleNetworkMessages();
	void OnSetClientIDPacket(RakNet::Packet* packet);

	void OnReceivedClientDataPacket(RakNet::Packet* packet);
	void OnReceivedClientDataPacketX(RakNet::Packet* packet);
	void OnReceivedClientDataPacketY(RakNet::Packet* packet);
	void OnReceivedClientDataPacketUpdate(RakNet::Packet* packet);

	void SendClientGameObject();
	void SendClientGameObjectStart();
	void SendDisconnect();
	void SendXCoordinates();
	void SendYCoordinates();
	
protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
	RakNet::RakPeerInterface* pPeerInterface;
	std::unordered_map<int, GameObject> otherClientGameObjects;
	const char* IP = "127.0.0.1";
	const unsigned short PORT = 5456;
	GameObject myGameObject;
	int myClientID = 0;
};