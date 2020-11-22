/*----------------------------------------
File Name: GameObject.h
Purpose: Makes game object for both
 server and client.
Author: Tarn Cooper
Modified: 25 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <glm/ext.hpp>
#include <RakPeerInterface.h>

//struct for game data
struct GameObjectData
{
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 colour;
	
};

//class for gameobject
class GameObject
{
public:
	GameObject();
	void Update(float deltaTime);
	void Write(RakNet::RakPeerInterface* pPeerInterface, const RakNet::SystemAddress& address, bool broadcast);
	void GameObject::Read(RakNet::Packet* packet);
	static glm::vec4 GetColour(int id);
	GameObjectData data;
	int id;
	int parentId;
	float lifetime;
	int points = 0;
};