/*----------------------------------------
File Name: Spring.h
Purpose:  Acts as a sphere joint of two objects in physics scene
Author: Tarn Cooper
Modified: 08 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Rigidbody.h"
class Spring : public Rigidbody
{
public:
	Spring(Rigidbody* body1, Rigidbody* body2, float inRestLength, float inSpringCoef, float inDamping = 0.1f, glm::vec2 inContact1 = glm::vec2(0, 0), glm::vec2 inContact2 = glm::vec2(0, 0));
	~Spring();
	virtual void FixedUpdate(glm::vec2 inGravity, float inTimeStep);
	virtual void MakeGizmo();
	
protected:
	Rigidbody* body1;
	Rigidbody* body2;

	glm::vec2 contact1;
	glm::vec2 contact2;

	float damping;
	float restLength;
	float springCoef;

};

