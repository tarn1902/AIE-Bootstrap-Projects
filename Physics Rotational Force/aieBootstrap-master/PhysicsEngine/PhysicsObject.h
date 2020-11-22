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
class Rigidbody;
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
	virtual void ResolveCollision(Rigidbody* rigidbody, glm::vec2 contact, glm::vec2* collisionNormal) = 0;
	virtual float GetElasticity() = 0;
	virtual void SetElasticity(float inElasticity) = 0;
	virtual float GetKineticEnergy() = 0;

protected:
	ShapeType shapeId;
	float Elasticity = 1;
};

