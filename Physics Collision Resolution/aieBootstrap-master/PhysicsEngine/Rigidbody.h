/*----------------------------------------
File Name: Rigidbody.h
Purpose: Gives a rigidbody to objects
Author: Tarn Cooper
Modified: 08 March 2020
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
	virtual void ResolveCollision(Rigidbody* actor2);
	glm::vec2 GetPosition();
	void SetPosition(glm::vec2 inPosition);
	float GetRotation();
	glm::vec2 GetVelocity();
	void SetVelocity(glm::vec2 inVelocity);
	float GetMass();
	void SetMass(float inMass);
	float GetLinearDrag();
	void SetLinearDrag(float inLinearDrag);
	float GetAngularDrag();
	void SetAngularDrag(float inAngularDrag);
	virtual float GetElasticity();
	virtual void SetElasticity(float inElasticity);

protected:
	float linearDrag = 0.3f;
	float angularDrag = 0.3f;
	float angularVelocity = 0;
	glm::vec2 position;
	glm::vec2 velocity;
	float mass;
	float rotation;
	float elasticity = 1;
	const static int MIN_LINEAR_THRESHOLD = 0.1f;
	const static int MIN_ROTATION_THRESHOLD = 0.01f;

};

