/*----------------------------------------
File Name: Rigidbody.cpp
Purpose: Gives a rigidbody to objects
Author: Tarn Cooper
Modified: 08 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Rigidbody.h"
#include <iostream>

//-----------------------------------------------------------
// Constructs Rigidbody
// inShapeId (ShapeType) : What type of shape is this object?
// inPosition (glm::vec2) : What position is this object at?
// inVelocity (glm::vec2) : What is the velocity if this object?
// inRotation (float) : What is the rotation of this object?
// inMass (float) : What is the mass of this object?
//-----------------------------------------------------------
Rigidbody::Rigidbody(ShapeType inShapeId, glm::vec2 inPosition, glm::vec2 inVelocity, float inRotation, float inMass) : PhysicsObject(inShapeId)
{
	position = inPosition;
	velocity = inVelocity;
	rotation = inRotation;
	mass = inMass;
}

//-----------------------------------------------------------
// Destructs rigidbody
//-----------------------------------------------------------
Rigidbody::~Rigidbody()
{

}

//-----------------------------------------------------------
// Updates object position with gravity and velocity
// inGravity (glm::vec2): What is the gravity on this object?
// inTimeStep (glm::vec2): What is the current time step?
//-----------------------------------------------------------
void Rigidbody::FixedUpdate(glm::vec2 inGravity, float inTimeStep)
{
	if (isKinematic)
	{
		return;
	}

	velocity += inGravity * inTimeStep;
	position += velocity * inTimeStep;

	velocity -= velocity * linearDrag * inTimeStep;
	rotation += angularVelocity * inTimeStep;
	angularVelocity -= angularVelocity * angularDrag * inTimeStep;

	if (glm::length(velocity) < MIN_LINEAR_THRESHOLD) {
		velocity = glm::vec2(0, 0);
	}
	if (glm::abs(angularVelocity) < MIN_ROTATION_THRESHOLD) {
		angularVelocity = 0;
	}
	
}

//-----------------------------------------------------------
// Able to debug each update
//-----------------------------------------------------------
void Rigidbody::Debug()
{

}

//-----------------------------------------------------------
// Applys velocity to object
//	inForce (glm::vec2): How much force is added?
//	inPos (glm::vec2): Where will force come from?
//-----------------------------------------------------------
void Rigidbody::ApplyForce(glm::vec2 inForce, glm::vec2 inPos)
{
	if (mass != 0)
	{
		velocity += inForce / mass;
		angularVelocity += (inForce.y * inPos.x - inForce.x * inPos.y) / moment;
	}
}

//-----------------------------------------------------------
// Get the position of object
// return (glm::vec2): Returns the position of object
//-----------------------------------------------------------
glm::vec2 Rigidbody::GetPosition() 
{ 
	return position; 
}
//-----------------------------------------------------------
// Get the rotation of object
// return (float): Returns the roation of object
//-----------------------------------------------------------
float Rigidbody::GetRotation() 
{ 
	return rotation; 
}

//-----------------------------------------------------------
// Get the velocity of object
// return (glm::vec2): Returns the velocity of object
//-----------------------------------------------------------
glm::vec2 Rigidbody::GetVelocity() 
{ 
	return velocity; 
}

//-----------------------------------------------------------
// Get the mass of object
// return (float): Returns the mass of object
//-----------------------------------------------------------
float Rigidbody::GetMass() 
{ 
	return (IsKinematic()) ?  INT_MAX : mass; 
}

//-----------------------------------------------------------
// Set the mass of object
// inMass (float): What is the mass of object?
//-----------------------------------------------------------
void Rigidbody::SetMass(float inMass)
{
	mass = inMass;
}

//-----------------------------------------------------------
// Set the position of object
// inPosition (glm::vec2): What is the position of object
//-----------------------------------------------------------
void Rigidbody::SetPosition(glm::vec2 inPosition)
{
	position = inPosition;
}

//-----------------------------------------------------------
// Set the velocity of object
// inVelocity (glm::vec2): What is the velocity of object
//-----------------------------------------------------------
void Rigidbody::SetVelocity(glm::vec2 inVelocity)
{
	velocity = inVelocity;
}

//-----------------------------------------------------------
// Resolves all collisions
//	inActor2 (Rigidbody*): What is other colliding object?
//	inContact (glm::vec2): Where is the contact point?
//	inCollisionNormal (glm::vec2): What is collision Normal?
//-----------------------------------------------------------
void Rigidbody::ResolveCollision(Rigidbody* inActor2, glm::vec2 inContact, glm::vec2* inCollisionNormal)
{
	//between two kinematic object
	if (isKinematic && inActor2->isKinematic)
	{
		return;
	}
	//between one kinematic object
	else if (!isKinematic && inActor2->isKinematic)
	{
		glm::vec2 vRel = GetVelocity();
		glm::vec2 normal = glm::normalize(GetPosition() - inActor2->GetPosition());
		float e = GetElasticity();
		float j = glm::dot(-(1 + e) * (vRel), normal) / (1 / GetMass());
		glm::vec2 force = normal * j;
		ApplyForce(-force, inContact -GetPosition());
	}
	//between other kinematic object
	else if (!inActor2->isKinematic && isKinematic)
	{
		
		glm::vec2 vRel = inActor2->GetVelocity();
		glm::vec2 normal = glm::normalize(GetPosition() - inActor2->GetPosition());
		float e = inActor2->GetElasticity();
		float j = glm::dot(-(1 + e) * (vRel), normal) / (1 / inActor2->GetMass());
		glm::vec2 force = normal * j;
		inActor2->ApplyForce(force, inContact - inActor2->GetPosition());
	}
	//between non kinemtic objects
	else
	{
		glm::vec2 normal = glm::normalize(inCollisionNormal ? *inCollisionNormal : inActor2->GetPosition() - position);

		glm::vec2 perp(normal.y, -normal.x);

		float r1 = glm::dot(inContact - position, -perp);
		float r2 = glm::dot(inContact - inActor2->position, perp);

		float v1 = glm::dot(velocity, normal) - r1 * angularVelocity;
		float v2 = glm::dot(inActor2->velocity, normal) + r2 * inActor2->angularVelocity;

		if (v1 > v2)
		{
			float mass1 = 1.0f / (1.0f / mass + (r1 * r1) / moment);
			float mass2 = 1.0f / (1.0f / inActor2->mass + (r2 * r2) / inActor2->moment);

			float elastic = (elasticity + inActor2->GetElasticity()) / 2.0f;

			glm::vec2 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal;

			//Add forces to both object
			ApplyForce(-force, inContact - position);
			inActor2->ApplyForce(force, inContact - inActor2->position);
		}
	}
}

//-----------------------------------------------------------
// Get the linear drag of object
// return (float): Returns the linear drag of object
//-----------------------------------------------------------
float Rigidbody::GetLinearDrag()
{
	return linearDrag;
}

//-----------------------------------------------------------
// Set the linear drag of object
// inLinearDrag (float): What is the linear drag of object?
//-----------------------------------------------------------
void Rigidbody::SetLinearDrag(float inLinearDrag)
{
	linearDrag = inLinearDrag;
}

//-----------------------------------------------------------
// Get the angular drag of object
// return (float): Returns the angular drag of object
//-----------------------------------------------------------
float Rigidbody::GetAngularDrag()
{
	return angularDrag;
}

//-----------------------------------------------------------
// Set the angular drag of object
// inAngularDrag (float): What is the angular drag of object?
//-----------------------------------------------------------
void Rigidbody::SetAngularDrag(float inAngularDrag)
{
	angularDrag = inAngularDrag;
}

//-----------------------------------------------------------
// Get the angular velocity of object
// return (float): Returns the angular velocity of object
//-----------------------------------------------------------
float Rigidbody::GetAngularVelocity()
{
	return angularVelocity;
}

//-----------------------------------------------------------
// Get the moment of object
// return (float): Returns the moment of object
//-----------------------------------------------------------
float Rigidbody::GetMoment()
{
	return moment;
}

//-----------------------------------------------------------
// Get the kinetic energy of object
// return (float): Returns the kinetic energy of object
//-----------------------------------------------------------
float Rigidbody::GetKineticEnergy()
{
	return 0.5f * (mass * glm::dot(velocity, velocity) + moment * angularVelocity * angularVelocity);
}

//-----------------------------------------------------------
// Check if is kinematic
// return (bool): Returns true if is kinematic of object
//-----------------------------------------------------------
bool Rigidbody::IsKinematic()
{
	return isKinematic;
}

//-----------------------------------------------------------
// Set the object as kinematic
// inState (bool): Is the object kinematic?
//-----------------------------------------------------------
void Rigidbody::SetKinematic(bool inState)
{
	isKinematic = inState;
}

//-----------------------------------------------------------
// Get world position of object
// return (glm::vec2): Returns world position of object
//-----------------------------------------------------------
glm::vec2 Rigidbody::ToWorld()
{
	float cs = cosf(rotation);
	float sn = sinf(rotation);

	glm::vec2 localX = glm::normalize(glm::vec2(cs, sn));
	glm::vec2 localY = glm::normalize(glm::vec2(-sn, cs));

	return GetPosition() + (localX * localX) + (localY * localY);
}