/*----------------------------------------
File Name: PhysicsObject.cpp
Purpose: Base class for all objects in physics scene
Author: Tarn Cooper
Modified: 06 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "PhysicsObject.h"

//-----------------------------------------------------------
// Constructs physics object
// inShapeId (ShapeType): What type of object is it?
//-----------------------------------------------------------
PhysicsObject::PhysicsObject(ShapeType inShapeId)
{
	shapeId = inShapeId;
}

//-----------------------------------------------------------
// Destructs physics object
//-----------------------------------------------------------
PhysicsObject::~PhysicsObject()
{

}

//-----------------------------------------------------------
// Get Shape ID of object
// return (ShapeType): Returns shape id of object
//-----------------------------------------------------------
ShapeType PhysicsObject::GetShapeId()
{
	return shapeId;
}

//-----------------------------------------------------------
// Sets colour of object
// onColour (glm::vec4): What colour should object be?
//-----------------------------------------------------------
void PhysicsObject::SetColour(glm::vec4 inColour)
{
	colour = inColour;
}

//-----------------------------------------------------------
// Get elasticity of object
// return (float): Returns elasticity of object
//-----------------------------------------------------------
float PhysicsObject::GetElasticity()
{
	return elasticity;
}

//-----------------------------------------------------------
// Set elasticity of object
// inElasticity (float): What elasticity is the object?
//-----------------------------------------------------------
void PhysicsObject::SetElasticity(float inElasticity)
{
	elasticity = inElasticity;
}