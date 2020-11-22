/*----------------------------------------
File Name: PhysicsScene.cpp
Purpose: Handles general scene set up in relation to physics objects
Author: Tarn Cooper
Modified: 10 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "PhysicsScene.h"
#include "Rigidbody.h"
#include <list>
#include <iostream>

//-----------------------------------------------------------
// Constructs physics scene
//-----------------------------------------------------------
PhysicsScene::PhysicsScene()
{
	timeStep = 0.01f;
	gravity = glm::vec2(0, 0);
}

//-----------------------------------------------------------
// Destructs physics scene
//-----------------------------------------------------------
PhysicsScene::~PhysicsScene()
{
	for (auto pActor : actors)
	{
		delete pActor;
	}
}

//-----------------------------------------------------------
// Add actor to scene
// inActor (PhysicsObject*): What actor will be added to scene
//-----------------------------------------------------------
void PhysicsScene::AddActor(PhysicsObject* inActor)
{
	actors.push_back(inActor);
}

//-----------------------------------------------------------
// Remove actor to scene
// inActor (PhysicsObject*): What actor will be removed from   scene
//-----------------------------------------------------------
void PhysicsScene::RemoveActor(PhysicsObject* inActor)
{
	actors.erase(std::find(actors.begin(), actors.end(), inActor));
}

//-----------------------------------------------------------
// Update object physics and checks for collision
// inDeltaTime (float): How long since last update?
//-----------------------------------------------------------
void PhysicsScene::Update(float inDeltaTime)
{
	static std::list<PhysicsObject*> dirty;
	// update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += inDeltaTime;
	while (accumulatedTime >= timeStep) {
		for (auto pActor : actors) {
			pActor->FixedUpdate(gravity, timeStep);
		}
		accumulatedTime -= timeStep;
		// check for collisions (ideally you'd want to have some sort of
		// scene management in place)
		for (auto pActor : actors) {
			for (auto pOther : actors) {
				if (pActor == pOther)
					continue;
				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
					continue;
				Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);
				if (pRigid->CheckCollision(pOther) == true) 
				{
					pRigid->ApplyForceToActor(dynamic_cast<Rigidbody*>(pOther), pRigid->GetVelocity()* pRigid->GetMass());
					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			}
		}
		dirty.clear();
	}
}

//-----------------------------------------------------------
// Update each actors visuals
//-----------------------------------------------------------
void PhysicsScene::UpdateGizmos()
{
	for (auto pActor : actors) {
		pActor->MakeGizmo();
	}

}

//-----------------------------------------------------------
// Set gravity of scene
// inGravity (const glm::vec2: What is the gravity of scene?
//-----------------------------------------------------------
void PhysicsScene::SetGravity(const glm::vec2 inGravity) 
{ 
	gravity = inGravity;
}

//-----------------------------------------------------------
// Get gravity of scene
// return (glm::vec2: Returns gravity of scene
//-----------------------------------------------------------
glm::vec2 PhysicsScene::GetGravity() const 
{ 
	return gravity; 
}

//-----------------------------------------------------------
// Set time step of scene
// inTimeStep (const glm::vec2: What is the time step of scene?
//-----------------------------------------------------------
void PhysicsScene::SetTimeStep(const float inTimeStep) 
{ 
	timeStep = inTimeStep; 
}

//-----------------------------------------------------------
// Get time step of scene
// return (glm::vec2: Returns time step of scene
//-----------------------------------------------------------
float PhysicsScene::GetTimeStep() const 
{ 
	return timeStep; 
}

//-----------------------------------------------------------
// Runs debug for each actor
//-----------------------------------------------------------
void PhysicsScene::DebugScene()
{
	int count = 0;
	for (auto pActor : actors) {
		std::cout << count << " : ";
		pActor->Debug();
		count++;
	}
}
