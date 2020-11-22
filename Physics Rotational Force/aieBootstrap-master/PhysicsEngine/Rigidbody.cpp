/*----------------------------------------
File Name: Rigidbody.cpp
Purpose: Gives a rigidbody to objects
Author: Tarn Cooper
Modified: 10 March 2020
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
	return mass; 
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
void Rigidbody::ResolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal)
{
	glm::vec2 normal = glm::normalize(collisionNormal ? *collisionNormal : actor2->GetPosition() - position);

	glm::vec2 perp(normal.y, -normal.x);

	float r1 = glm::dot(contact - position, -perp);
	float r2 = glm::dot(contact - actor2->position, perp);

	float v1 = glm::dot(velocity, normal) - r1 * angularVelocity;
	float v2 = glm::dot(actor2->velocity, normal) + r2 * actor2->angularVelocity;

	if (v1 > v2)
	{
		float mass1 = 1.0f / (1.0f / mass + (r1 * r1) / moment);
		float mass2 = 1.0f / (1.0f / actor2->mass + (r2 * r2) / actor2->moment);

		float elastic = (elasticity + actor2->GetElasticity()) / 2.0f;

		glm::vec2 force = (1.0f + elasticity) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2)* normal;


		ApplyForce(-force, contact - position);
		actor2->ApplyForce(force, contact - actor2->position);

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
// Get the elasticity of object
// return (float): returns the elasticity of object?
//-----------------------------------------------------------
float Rigidbody::GetElasticity()
{
	return elasticity;
}

//-----------------------------------------------------------
// Get the elasticity of object
// inElasticity (float): What is the elasticity of object?
//-----------------------------------------------------------
void Rigidbody::SetElasticity(float inElasticity)
{
	elasticity = inElasticity;
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
// Set the object as kinematic
// inState (bool): Is the object kinematic?
//-----------------------------------------------------------
bool Rigidbody::IsKinematic()
{
	return false;
}