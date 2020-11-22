/*----------------------------------------
File Name: PhysicsObject.h
Purpose: Base class for all objects in physics scene
Author: Tarn Cooper
Modified: 06 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <glm/ext.hpp>
#include "ShapeType.h"

class Rigidbody;
class PhysicsObject
{
protected:
	PhysicsObject(ShapeType inShapeId);
public:
	virtual ~PhysicsObject();
	virtual void FixedUpdate(glm::vec2 inGravity, float inTimeStep) = 0;
	virtual void Debug() = 0;
	virtual void MakeGizmo() = 0;
	ShapeType GetShapeId();
	virtual void ResolveCollision(Rigidbody* inRigidbody, glm::vec2 inContact, glm::vec2* inCollisionNormal) = 0;
	float GetElasticity();
	void SetElasticity(float inElasticity);
	virtual float GetKineticEnergy() = 0;
	void SetColour(glm::vec4 inColour);

protected:
	ShapeType shapeId;
	float elasticity = 1;
	glm::vec4 colour;
};

