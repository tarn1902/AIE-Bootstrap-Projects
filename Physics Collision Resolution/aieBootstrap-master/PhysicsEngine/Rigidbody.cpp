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
	if (glm::length(velocity) < MIN_LINEAR_THRESHOLD) {
		velocity = glm::vec2(0, 0);
	}
	if (glm::abs(angularVelocity) < MIN_ROTATION_THRESHOLD) {
		angularVelocity = 0;
	}
	ApplyForce(inGravity * mass * inTimeStep);
	velocity -= velocity * linearDrag * inTimeStep;
	angularVelocity -= angularVelocity * angularDrag * inTimeStep;
	position += velocity * inTimeStep;
	
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
void Rigidbody::ApplyForce(glm::vec2 inForce)
{
	if (mass != 0)
	{
		velocity += -inForce / mass;
	}
}

//-----------------------------------------------------------
// Applys opposite velocitys to objects
//	inActor2 (Rigidbody*) : What is the collided actor
//	inForce (glm::vec2): How much force is added?
//-----------------------------------------------------------
void Rigidbody::ApplyForceToActor(Rigidbody* inActor2, glm::vec2 inForce)
{
	ApplyForce(inForce);
	inActor2->ApplyForce(-inForce);
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
void Rigidbody::ResolveCollision(Rigidbody* actor2)
{
	glm::vec2 normal = glm::normalize(actor2->GetPosition() - position);
	glm::vec2 relativeVelocity = actor2->GetVelocity() - velocity;
	float elastic = (elasticity + actor2->GetElasticity()) / 2.0f;
	float j = glm::dot(-(1 + elastic) * (relativeVelocity), normal) /glm::dot(normal, normal * ((1 / mass) + (1 / actor2->GetMass())));
	glm::vec2 force = normal * j;
	ApplyForceToActor(actor2, force);
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
// return (float): Returns the elasticity of object
//-----------------------------------------------------------
float Rigidbody::GetElasticity()
{
	return elasticity;
}

//-----------------------------------------------------------
// Set the elasticity of object
// return (float): Returns the elasticity of object
//-----------------------------------------------------------
void Rigidbody::SetElasticity(float inElasticity)
{
	elasticity = inElasticity;
}