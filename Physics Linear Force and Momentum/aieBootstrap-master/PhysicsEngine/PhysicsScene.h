/*----------------------------------------
File Name: PhysicsScene.h
Purpose: Handles general scene set up in relation to physics objects
Author: Tarn Cooper
Modified: 10 March 2020
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
	void Update(float dt);
	void UpdateGizmos();
	void SetGravity(const glm::vec2 inGravity);
	glm::vec2 GetGravity() const;
	void SetTimeStep(const float inTimeStep);
	float GetTimeStep() const;
	void DebugScene();
protected:
	glm::vec2 gravity;
	float timeStep;
	std::vector<PhysicsObject*> actors;
};

