/*----------------------------------------
File Name: GameObject.cpp
Purpose: Function of gameobject class
Author: Tarn Cooper
Modified: 25 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "GameObject.h"
#include "GameMessages.h"
#include <BitStream.h>

//-----------------------------------------------------------
// Constructs gameobject
//-----------------------------------------------------------
GameObject::GameObject()
{
	data.position = glm::vec3(0);
	data.colour = glm::vec4(1, 1, 1, 1);
}

//-----------------------------------------------------------
// Writes gameobject data
// pPeerInterface (RakNet::RakPeerInterface*): What is the 
//  interface?
// address (const RakNet::SystemAddress&): Where will it be 
//  sent?
// broadcast (bool): Will it be broadcast?
//-----------------------------------------------------------
void GameObject::Write(RakNet::RakPeerInterface* pPeerInterface, const RakNet::SystemAddress& address, bool broadcast)
{
	RakNet::BitStream bs;
	bs.Write((RakNet::MessageID)GameMessages::ID_CLIENT_CLIENT_DATA);
	bs.Write(id);
	bs.Write((char*)& data, sizeof(GameObjectData));
	pPeerInterface->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
		address, broadcast);

}

//-----------------------------------------------------------
// Handles message for gameobject
// packet (RakNet::Packet*): What was packet caught?
//-----------------------------------------------------------
void GameObject::Read(RakNet::Packet* packet)
{
	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
	bsIn.Read(id);
	bsIn.Read((char*)& data, sizeof(GameObjectData));
}

//array of colours
glm::vec4 colours[] = {
	glm::vec4(0.5,0.5,0.5,1), //grey
	glm::vec4(1,0,0,1), // red
	glm::vec4(0,1,0,1), // green
	glm::vec4(0,0,1,1), // blue
	glm::vec4(1,1,0,1), // yellow
	glm::vec4(1,0,1,1), // magenta
	glm::vec4(0,1,1,1), //cyan
	glm::vec4(0,0,0,1), //black
};

//-----------------------------------------------------------
// Gets colour depending on id
// id (int): What is the gameobjects id?
// return (glm::vec4): returns colour
//-----------------------------------------------------------
glm::vec4 GameObject::GetColour(int id)
{
	return colours[id & 7];
}

//-----------------------------------------------------------
// Updates objects position
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
void GameObject::Update(float deltaTime)
{
	data.position += data.velocity * deltaTime;
}