/*----------------------------------------
File Name: PhysicsObject.cpp
Purpose: Base class for all objects in physics scene
Author: Tarn Cooper
Modified: 10 March 2020
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
// Get Shape ID of object
// return (ShapeType): Returns shape id of object
//-----------------------------------------------------------
ShapeType PhysicsObject::GetShapeId()
{
	return shapeId;
}