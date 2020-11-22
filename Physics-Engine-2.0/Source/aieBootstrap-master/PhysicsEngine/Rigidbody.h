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

protected:
	Rigidbody(ShapeType inShapeID, glm::vec2 inPosition, glm::vec2 inVelocity, float inRotation, float inMass);
	virtual ~Rigidbody();
public:
	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void Debug();
	virtual void MakeGizmo() = 0;
	virtual void ResolveCollision(Rigidbody* inActor2, glm::vec2 inContact, glm::vec2* inCollisionNormal = nullptr);
	void ApplyForce(glm::vec2 inForce, glm::vec2 inPos);
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
	float GetAngularVelocity();
	float GetMoment();
	virtual float GetKineticEnergy();
	bool IsKinematic();
	void SetKinematic(bool inState);
	glm::vec2 ToWorld();

protected:
	float linearDrag = 0.3f;
	float angularDrag = 0.3f;
	float angularVelocity = 0;
	glm::vec2 position;
	glm::vec2 velocity;
	float mass;
	float rotation;
	float moment = 0;
	const static int MIN_LINEAR_THRESHOLD = 0.1f;
	const static int MIN_ROTATION_THRESHOLD = 0.01f;
	bool isKinematic = false;

};

