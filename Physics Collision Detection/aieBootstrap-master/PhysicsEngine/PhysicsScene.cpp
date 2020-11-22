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
#include "Plane.h"
#include "Sphere.h"
#include "Box.h"

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] =
{
PhysicsScene::Plane2Plane, PhysicsScene::Plane2Sphere, PhysicsScene::Plane2Box,
PhysicsScene::Sphere2Plane, PhysicsScene::Sphere2Sphere, PhysicsScene::Sphere2Box,
PhysicsScene::Box2Plane, PhysicsScene::Box2Sphere, PhysicsScene::Box2Box,
};

//-----------------------------------------------------------
// Checks collision between actors
//-----------------------------------------------------------
void PhysicsScene::CheckForCollision()
{
	int actorCount = actors.size();
	//need to check for collisions against all objects except this one.
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = actors[outer];
			PhysicsObject* object2 = actors[inner];
			int shapeId1 = object1->GetShapeId();
			int shapeId2 = object2->GetShapeId();
			// using function pointers
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				// did a collision occur?
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

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
		CheckForCollision();
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

//-----------------------------------------------------------
// Test for plane to plane collision
// inObj1 (PhysicsObject*): What is first object?
// inObj1 (PhysicsObject*): What is second object?
// return (bool): returns if collision occured
//-----------------------------------------------------------
bool PhysicsScene::Plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

//-----------------------------------------------------------
// Test for plane to sphere collision
// inObj1 (PhysicsObject*): What is first object?
// inObj1 (PhysicsObject*): What is second object?
// return (bool): returns if collision occured
//-----------------------------------------------------------
bool PhysicsScene::Plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj2);
	Plane* plane = dynamic_cast<Plane*>(obj1);
	//if we are successful then test for collision
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->GetNormal();
		float sphereToPlane = glm::dot(sphere->GetPosition(), plane->GetNormal()) - plane->GetDistance();
		// if we are behind plane then we flip the normal
		if (sphereToPlane < 0) {
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}
		float intersection = sphere->GetRadius() - sphereToPlane;
		if (intersection > 0)
		{
			sphere->SetVelocity(glm::vec2(0, 0));
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------
// Test for sphere to plane collision
// inObj1 (PhysicsObject*): What is first object?
// inObj1 (PhysicsObject*): What is second object?
// return (bool): returns if collision occured
//-----------------------------------------------------------
bool PhysicsScene::Sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);
	//if we are successful then test for collision
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->GetNormal();
		float sphereToPlane = glm::dot(sphere->GetPosition(), plane->GetNormal()) - plane->GetDistance();
		// if we are behind plane then we flip the normal
		if (sphereToPlane < 0) {
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}
		float intersection = sphere->GetRadius() - sphereToPlane;
		if (intersection > 0) 
		{
			sphere->SetVelocity(glm::vec2(0, 0));
			return true;
		}
	}
	return false;

}

//-----------------------------------------------------------
// Test for sphere to sphere collision
// inObj1 (PhysicsObject*): What is first object?
// inObj1 (PhysicsObject*): What is second object?
// return (bool): returns if collision occured
//-----------------------------------------------------------
bool PhysicsScene::Sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);
	//if we are successful then test for collision
	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		return sphere1->CheckCollision(sphere2);
	}
}

//-----------------------------------------------------------
// Test for plane to box collision
// inObj1 (PhysicsObject*): What is first object?
// inObj1 (PhysicsObject*): What is second object?
// return (bool): returns if collision occured
//-----------------------------------------------------------
bool PhysicsScene::Plane2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box = dynamic_cast<Box*>(obj2);
	Plane* plane = dynamic_cast<Plane*>(obj1);
	//if we are successful then test for collision
	if (box != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->GetNormal();
		float boxToPlane = glm::dot(box->GetPosition(), plane->GetNormal()) - plane->GetDistance();

		if (boxToPlane < 0)
		{
			collisionNormal *= -1;
			boxToPlane *= -1;
		}

		if (boxToPlane - box->GetExtents().x < 0 || boxToPlane - box->GetExtents().y < 0)
		{
			box->SetVelocity(glm::vec2(0, 0));
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------
// Test for sphere to box collision
// inObj1 (PhysicsObject*): What is first object?
// inObj1 (PhysicsObject*): What is second object?
// return (bool): returns if collision occured
//-----------------------------------------------------------
bool PhysicsScene::Sphere2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box = dynamic_cast<Box*>(obj2);
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	//if we are successful then test for collision
	if (box != nullptr && sphere != nullptr)
	{
		glm::vec2 corners[] = {
			glm::vec2(box->GetPosition().x - box->GetExtents().x, box->GetPosition().y - box->GetExtents().y),
			glm::vec2(box->GetPosition().x + box->GetExtents().x, box->GetPosition().y - box->GetExtents().y),
			glm::vec2(box->GetPosition().x - box->GetExtents().x, box->GetPosition().y + box->GetExtents().y),
			glm::vec2(box->GetPosition().x + box->GetExtents().x, box->GetPosition().y + box->GetExtents().y)
		};
		glm::vec2 closestCorner = corners[0];
		for each (glm::vec2 corner in corners)
		{
			if (glm::distance(sphere->GetPosition(), corner) < glm::distance(sphere->GetPosition(), closestCorner))
			{
				closestCorner = corner;
			}
		}
		std::cout << glm::distance(closestCorner, sphere->GetPosition()) << std::endl;
		std::cout << sphere->GetRadius() << std::endl;
		if (glm::distance(closestCorner, sphere->GetPosition()) < sphere->GetRadius())
		{
			box->SetVelocity(glm::vec2(0, 0));
			sphere->SetVelocity(glm::vec2(0, 0));
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------
// Test for box to plane collision
// inObj1 (PhysicsObject*): What is first object?
// inObj1 (PhysicsObject*): What is second object?
// return (bool): returns if collision occured
//-----------------------------------------------------------
bool PhysicsScene::Box2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box = dynamic_cast<Box*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);
	//if we are successful then test for collision
	if (box != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->GetNormal();
		float boxToPlane = glm::dot(box->GetPosition(), plane->GetNormal()) - plane->GetDistance();

		if (boxToPlane < 0)
		{
			collisionNormal *= -1;
			boxToPlane *= -1;
		}

		if (boxToPlane - box->GetExtents().x < 0 || boxToPlane - box->GetExtents().y < 0)
		{
			box->SetVelocity(glm::vec2(0, 0));
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------
// Test for box to sphere collision
// inObj1 (PhysicsObject*): What is first object?
// inObj1 (PhysicsObject*): What is second object?
// return (bool): returns if collision occured
//-----------------------------------------------------------
bool PhysicsScene::Box2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box = dynamic_cast<Box*>(obj1);
	Sphere* sphere = dynamic_cast<Sphere*>(obj2);
	glm::vec2 corners[] = {
			glm::vec2(box->GetPosition().x - box->GetExtents().x, box->GetPosition().y - box->GetExtents().y),
			glm::vec2(box->GetPosition().x + box->GetExtents().x, box->GetPosition().y - box->GetExtents().y),
			glm::vec2(box->GetPosition().x - box->GetExtents().x, box->GetPosition().y + box->GetExtents().y),
			glm::vec2(box->GetPosition().x + box->GetExtents().x, box->GetPosition().y + box->GetExtents().y)
	};
	//if we are successful then test for collision
	if (box != nullptr && sphere != nullptr)
	{
		glm::vec2 clamped = glm::clamp(sphere->GetPosition(), corners[0], corners[3]);

		if (glm::distance(sphere->GetPosition(), clamped) < sphere->GetRadius())
		{
			box->SetVelocity(glm::vec2(0, 0));
			sphere->SetVelocity(glm::vec2(0, 0));
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------
// Test for box to box collision
// inObj1 (PhysicsObject*): What is first object?
// inObj1 (PhysicsObject*): What is second object?
// return (bool): returns if collision occured.
//-----------------------------------------------------------
bool PhysicsScene::Box2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);
	//if we are successful then test for collision
	if (box1 != nullptr && box2 != nullptr)
	{
		return box1->CheckCollision(box2);
	}
}
