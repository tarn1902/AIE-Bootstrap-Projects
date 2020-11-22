/*----------------------------------------
File Name: Server.h
Purpose: Holds game object for both
 server and client.
Author: Tarn Cooper
Modified: 18 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <map>
#include "GameObject.h"
//Class for server
class Server
{
public:
	void StartUp();
	void SendNewClientID(RakNet::SystemAddress& address);
	void HandleNetworkMessages();
	void OnSpawnBullet(RakNet::Packet* packet);
	void SpawnObject(glm::vec3 position, glm::vec3 velocity, int parentID);
	static void UpdateThread(Server* server, RakNet::RakPeerInterface* pPeerInterface);
	void Despawn(int id);
	void SendScores(int id);
	std::map<int, GameObject> gameObjects;
	int nextClientID = 1;
	int nextServerID = 1000;
	RakNet::RakPeerInterface* pPeerInterface = nullptr;
	
};

