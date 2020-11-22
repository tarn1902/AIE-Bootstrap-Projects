/*----------------------------------------
File Name: Plane.h
Purpose: Acts as a plane in physics scene
Author: Tarn Cooper
Modified: 10 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "PhysicsObject.h"
#include "Rigidbody.h"
class Plane : public PhysicsObject
{
public:
	Plane();
	Plane(glm::vec2 normal, float distance);
	~Plane();
	virtual void FixedUpdate(glm::vec2 inGravity, float inTimeStep);
	virtual void Debug();
	virtual void MakeGizmo();
	glm::vec2 GetNormal();
	float GetDistance();
	virtual void ResolveCollision(Rigidbody* rigidbody, glm::vec2 contact, glm::vec2* collisionNormal);
	virtual float GetElasticity();
	virtual void SetElasticity(float inElasticity);
	virtual float GetKineticEnergy();
protected:
	glm::vec2 normal;
	float distanceToOrigin;
	float elasticity = 1;
};


