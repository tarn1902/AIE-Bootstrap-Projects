/*----------------------------------------
File Name: Client.h
Purpose: Makes client game for server
Author: Tarn Cooper
Modified: 25 May 2020
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

	void SendClientGameObject();

	void OnRecievedClientDataPacket(RakNet::Packet* packet);

	void SendSpawnBulletPacket();

	void OnDespawn(RakNet::Packet* packet);

	void OnRecievedPoints(RakNet::Packet* packet);

protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	RakNet::RakPeerInterface* pPeerInterface;

	std::unordered_map<int, GameObject> otherClientGameObjects;

	const char* IP = "127.0.0.1";
	const unsigned short PORT = 5456;
	GameObject myGameObject;
	glm::vec3 facing = glm::vec3(0, 1, 0);
	bool wasKeyDown = false;
};