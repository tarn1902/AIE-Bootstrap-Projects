/*----------------------------------------
File Name: Rigidbody.h
Purpose: Gives a rigidbody to objects
Author: Tarn Cooper
Modified: 10 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "PhysicsObject.h"
class Rigidbody : public PhysicsObject {
public:
	Rigidbody(ShapeType shapeID, glm::vec2 position,
		glm::vec2 velocity, float rotation, float mass);
	~Rigidbody();
	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void Debug();
	void ApplyForce(glm::vec2 force);
	void ApplyForceToActor(Rigidbody* actor2, glm::vec2 force);
	virtual bool CheckCollision(PhysicsObject* pOther) = 0;
	glm::vec2 GetPosition();
	void SetPosition(glm::vec2 inPosition);
	float GetRotation();
	glm::vec2 GetVelocity();
	float GetMass();
	void SetMass(float inMass);
protected:
	glm::vec2 position;
	glm::vec2 velocity;
	float mass;
	float rotation;
};

