/*----------------------------------------
File Name: GameObject.h
Purpose: Holds game object for both
 server and client.
Author: Tarn Cooper
Modified: 18 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <glm/ext.hpp>.
//Structure for game objects
struct GameObject
{
	glm::vec3 position;
	glm::vec4 colour;
};