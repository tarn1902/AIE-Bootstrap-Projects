/*----------------------------------------
File Name: FlyCamera.h
Purpose: Structure of Fly Camera class
Author: Tarn Cooper
Modified: 27 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Camera.h"
//Fly Camera Class
class FlyCamera : public Camera
{
public:
	FlyCamera();
	virtual void Update(float deltaTime);
	void SetSpeed(float speed);
	glm::vec3 GetCurrentSpeed();

private:
	float speed;
	glm::vec3 up;
	glm::vec3 worldSpeed;
};