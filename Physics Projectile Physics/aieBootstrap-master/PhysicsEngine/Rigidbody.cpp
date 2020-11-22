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
	ApplyForce(inGravity * mass * inTimeStep);
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
		velocity += inForce / mass;
	}
}

//-----------------------------------------------------------
// Applys opposite velocitys to objects
//	inActor2 (Rigidbody*) : What is the collided actor
//	inForce (glm::vec2): How much force is added?
//-----------------------------------------------------------
void Rigidbody::ApplyForceToActor(Rigidbody* inActor2, glm::vec2 inForce)
{
	ApplyForce(-inForce);
	inActor2->ApplyForce(inForce);
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