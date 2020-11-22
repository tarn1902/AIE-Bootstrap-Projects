/*----------------------------------------
File Name: PhysicsScene.h
Purpose: Handles general scene set up in relation to physics objects
Author: Tarn Cooper
Modified: 06 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <glm/ext.hpp>
#include <vector>
#include "PhysicsObject.h"
class PhysicsScene
{
public:
	PhysicsScene();
	~PhysicsScene();
	void AddActor(PhysicsObject* inActor);
	void RemoveActor(PhysicsObject* inActor);
	void Update(float inDeltaTime);
	void UpdateGizmos();
	void DebugScene();
	void SetGravity(const glm::vec2 inGravity);
	glm::vec2 GetGravity() const;
	void SetTimeStep(const float inTimeStep);
	float GetTimeStep() const;
	void CheckForCollision();
	static bool Plane2Plane(PhysicsObject* inObj1, PhysicsObject* inObj2);
	static bool Plane2Sphere(PhysicsObject* inObj1, PhysicsObject* inObj2);
	static bool Sphere2Plane(PhysicsObject* inObj1, PhysicsObject* inObj2);
	static bool Sphere2Sphere(PhysicsObject* inObj1, PhysicsObject* inObj2);
	static bool Plane2Box(PhysicsObject* inObj1, PhysicsObject* inObj2);
	static bool Sphere2Box(PhysicsObject* inObj1, PhysicsObject* inObj2);
	static bool Box2Plane(PhysicsObject* inObj1, PhysicsObject* inObj2);
	static bool Box2Sphere(PhysicsObject* inObj1, PhysicsObject* inObj2);
	static bool Box2Box(PhysicsObject* inObj1, PhysicsObject* inObj2);
	static void ApplyContactForces(Rigidbody* inBody1, Rigidbody* inBody2, glm::vec2 inNorm, float inPen);
	std::vector<PhysicsObject*> GetActors();
protected:
	glm::vec2 gravity;
	float timeStep;
	std::vector<PhysicsObject*> actors;
};


