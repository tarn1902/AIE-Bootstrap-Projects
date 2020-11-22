/*----------------------------------------
File Name: PhysicsObject.h
Purpose: Base class for all objects in physics scene
Author: Tarn Cooper
Modified: 10 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <glm/ext.hpp>
enum ShapeType
{
	PLANE = 0,
	SPHERE,
	BOX,
	SHAPE_COUNT
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType inShapeId);
public:
	~PhysicsObject();
	virtual void FixedUpdate(glm::vec2 inGravity, float inTimeStep) = 0;
	virtual void Debug() = 0;
	virtual void MakeGizmo() = 0;
	ShapeType GetShapeId();

protected:
	ShapeType shapeId;
};

