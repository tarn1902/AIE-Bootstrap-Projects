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
#include "OOB.h"

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
				{
					float kePre = object1->GetKineticEnergy()
						+ object2->GetKineticEnergy();
					// did a collision occur?
					collisionFunctionPtr(object1, object2);
					float kePost = object1->GetKineticEnergy()
						+ object2->GetKineticEnergy();
					float deltaKe = kePost - kePre;
					if (deltaKe < -0.01f || deltaKe > 0.01f)
						std::cout << "Energy change detected!" << std::endl;
				}
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
			sphere->SetPosition(sphere->GetPosition() + plane->GetNormal() * (sphere->GetRadius() - sphereToPlane));
			Rigidbody* rbSphere1 = dynamic_cast<Rigidbody*>(obj2);
			plane->ResolveCollision(rbSphere1, sphere->GetPosition() + (collisionNormal * -sphere->GetRadius()), nullptr);
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
			sphere->SetPosition(sphere->GetPosition() + collisionNormal * (sphere->GetRadius() - sphereToPlane));
			Rigidbody* rbSphere1 = dynamic_cast<Rigidbody*>(obj1);
			plane->ResolveCollision(rbSphere1, sphere->GetPosition() + (collisionNormal * -sphere->GetRadius()), nullptr);
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
			glm::vec2 delta = sphere2->GetPosition() - sphere1->GetPosition();
			float distance = glm::length(delta);
			float intersection = sphere1->GetRadius() + sphere2->GetRadius() - distance;
			if (intersection > 0)
			{
				Rigidbody* rbSphere1 = dynamic_cast<Rigidbody*>(obj1);
				Rigidbody* rbSphere2 = dynamic_cast<Rigidbody*>(obj2);
				glm::vec2 contactForce = 0.5f * (distance - (sphere1->GetRadius() + sphere2->GetRadius())) * delta / distance;
				sphere1->SetPosition(sphere1->GetPosition() + contactForce);
				sphere2->SetPosition(sphere2->GetPosition() - contactForce);
				rbSphere1->ResolveCollision(rbSphere2, 0.5f * (sphere1->GetPosition() + sphere2->GetPosition()));
				return true;
			}
		}
	return false;
}

//-----------------------------------------------------------
// Test for plane to box collision
// inObj1 (PhysicsObject*): What is first object?
// inObj1 (PhysicsObject*): What is second object?
// return (bool): returns if collision occured
//-----------------------------------------------------------
bool PhysicsScene::Plane2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	OOB* box = dynamic_cast<OOB*>(obj2);
	Plane* plane = dynamic_cast<Plane*>(obj1);
	//if we are successful then test for collision
	if (box != nullptr && plane != nullptr)
	{
		int numContacts = 0;
		glm::vec2 contact(0, 0);
		float contactV = 0;
		float radius = 0.5f * std::fminf(box->GetWidth(), box->GetHeight());
		float penetration = 0;


		glm::vec2 planeOrigin = plane->GetNormal() * plane->GetDistance();
		float comFromPlane = glm::dot(box->GetPosition() - planeOrigin, plane->GetNormal());

		for (float x = -box->GetExtents().x; x < box->GetWidth(); x += box->GetWidth())
		{
			for (float y = -box->GetExtents().y; y < box->GetHeight(); y += box->GetHeight())
			{
				glm::vec2 p = box->GetPosition() + x * box->GetLocalX() + y * box->GetLocalY();
				float disFromPlane = glm::dot(p - planeOrigin, plane->GetNormal());

				float velocityIntoPlane = glm::dot(box->GetVelocity() + box->GetAngularVelocity() * (-y * box->GetLocalX() + x * box->GetLocalY()), plane->GetNormal());

				if ((disFromPlane > 0 && comFromPlane < 0 && velocityIntoPlane > 0) || (disFromPlane < 0 && comFromPlane > 0 && velocityIntoPlane < 0))
				{
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;

					if (comFromPlane >= 0) {
						if (penetration > disFromPlane)
							penetration = disFromPlane;
					}
					else {
						if (penetration < disFromPlane)
							penetration = disFromPlane;
					}
				}
			}
		}

		if (numContacts > 0)
		{
			float collisionV = contactV / (float)numContacts;
			glm::vec2 acceleration = -plane->GetNormal() * (1.0f + box->GetElasticity() * collisionV);
			glm::vec2 localContact = (contact / (float)numContacts) - box->GetPosition();
			float r = glm::dot(localContact, glm::vec2(plane->GetNormal().y, -plane->GetNormal().x));
			float mass0 = 1.0f / (1.0f / box->GetMass() + (r * r) / box->GetMoment());
			box->ApplyForce(acceleration * mass0, localContact);
			box->SetPosition(box->GetPosition() - plane->GetNormal() * penetration);
			
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
	OOB* box = dynamic_cast<OOB*>(obj2);
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	if (box != nullptr && sphere != nullptr) {
		glm::vec2 circlePos = sphere->GetPosition() - box->GetPosition();
		float w2 = box->GetWidth() / 2, h2 = box->GetHeight() / 2;
		int numContacts = 0;
		glm::vec2 contact(0, 0); // contact is in our box coordinates
		// check the four corners to see if any of them are inside the circle
		for (float x = -w2; x <= w2; x += box->GetWidth()) {
			for (float y = -h2; y <= h2; y += box->GetHeight()) {
				glm::vec2 p = x * box->GetLocalX() + y * box->GetLocalY();
				glm::vec2 dp = p - circlePos;
				if (dp.x * dp.x + dp.y * dp.y < sphere->GetRadius() * sphere->GetRadius()) {
					numContacts++;
					contact += glm::vec2(x, y);
				}
			}
		}
		glm::vec2* direction = nullptr;
		// get the local position of the circle centre
		glm::vec2 localPos(glm::dot(box->GetLocalX(), circlePos),
			glm::dot(box->GetLocalY(), circlePos));
		if (localPos.y < h2 && localPos.y > -h2) {
			if (localPos.x > 0 && localPos.x < w2 + sphere->GetRadius()) {
				numContacts++;
				contact += glm::vec2(w2, localPos.y);
				direction = new glm::vec2(box->GetLocalX());
			}
			if (localPos.x < 0 && localPos.x > -(w2 + sphere->GetRadius())) {
				numContacts++;
				contact += glm::vec2(-w2, localPos.y);
				direction = new glm::vec2(-box->GetLocalX());
			}
		}
		if (localPos.x < w2 && localPos.x > -w2)
		{
			if (localPos.y > 0 && localPos.y < h2 + sphere->GetRadius())
			{
				numContacts++;
				contact += glm::vec2(localPos.x, h2);
				direction = new glm::vec2(box->GetLocalY());
			}
			if (localPos.y < 0 && localPos.y > -(h2 + sphere->GetRadius()))
			{
				numContacts++;
				contact += glm::vec2(localPos.x, -h2);
				direction = new glm::vec2(-box->GetLocalY());
			}
		}
		if (numContacts > 0)
		{
			// average, and convert back into world coords
			contact = box->GetPosition() + (1.0f / numContacts) * (box->GetLocalX() * contact.x + box->GetLocalY() * contact.y);
			box->ResolveCollision(sphere, contact, direction);
			float pen = sphere->GetRadius() - glm::length(contact - sphere->GetPosition());
			glm::vec2 norm = glm::normalize(sphere->GetPosition() - contact);
			ApplyContactForces(sphere, box, norm, pen);
		}
		delete direction;
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
	OOB* box = dynamic_cast<OOB*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);
	//if we are successful then test for collision
	if (box != nullptr && plane != nullptr)
	{
		int numContacts = 0;
		glm::vec2 contact(0, 0);
		float contactV = 0;
		float radius = 0.5f * std::fminf(box->GetWidth(), box->GetHeight());
		float penetration = 0;


		glm::vec2 planeOrigin = plane->GetNormal() * plane->GetDistance();
		float comFromPlane = glm::dot(box->GetPosition() - planeOrigin, plane->GetNormal());

		for (float x = -box->GetExtents().x; x < box->GetWidth(); x += box->GetWidth())
		{
			for (float y = -box->GetExtents().y; y < box->GetHeight(); y += box->GetHeight())
			{
				glm::vec2 p = box->GetPosition() + x * box->GetLocalX() + y * box->GetLocalY();
				float disFromPlane = glm::dot(p - planeOrigin, plane->GetNormal());

				float velocityIntoPlane = glm::dot(box->GetVelocity() + box->GetAngularVelocity() * (-y * box->GetLocalX() + x * box->GetLocalY()), plane->GetNormal());

				if ((disFromPlane > 0 && comFromPlane < 0 && velocityIntoPlane >= 0 || disFromPlane < 0 && comFromPlane > 0 && velocityIntoPlane <= 0))
				{
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;

					if (comFromPlane >= 0) {
						if (penetration > disFromPlane)
							penetration = disFromPlane;
					}
					else {
						if (penetration < disFromPlane)
							penetration = disFromPlane;
					}
				}
			}
		}

		if (numContacts > 0)
		{
			float collisionV = contactV / (float)numContacts;
			glm::vec2 acceleration = -plane->GetNormal() * (1.0f + box->GetElasticity() * collisionV);
			glm::vec2 localContact = (contact / (float)numContacts) - box->GetPosition();
			float r = glm::dot(localContact, glm::vec2(plane->GetNormal().y, -plane->GetNormal().x));
			float mass0 = 1.0f / (1.0f / box->GetMass() + (r * r) / box->GetMoment());
			box->ApplyForce(acceleration * mass0, localContact);
			box->SetPosition(box->GetPosition() - plane->GetNormal() * penetration);
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
	OOB* box = dynamic_cast<OOB*>(obj1);
	Sphere* sphere = dynamic_cast<Sphere*>(obj2);
	if (box != nullptr && sphere != nullptr) {
		glm::vec2 circlePos = sphere->GetPosition() - box->GetPosition();
		float w2 = box->GetWidth() / 2, h2 = box->GetHeight() / 2;
		int numContacts = 0;
		glm::vec2 contact(0, 0); // contact is in our box coordinates
		// check the four corners to see if any of them are inside the circle
		for (float x = -w2; x <= w2; x += box->GetWidth()) {
			for (float y = -h2; y <= h2; y += box->GetHeight()) {
				glm::vec2 p = x * box->GetLocalX() + y * box->GetLocalY();
				glm::vec2 dp = p - circlePos;
				if (dp.x * dp.x + dp.y * dp.y < sphere->GetRadius() * sphere->GetRadius()) {
					numContacts++;
					contact += glm::vec2(x, y);
				}

			}
		}
		glm::vec2* direction = nullptr;
		// get the local position of the circle centre
		glm::vec2 localPos(glm::dot(box->GetLocalX(), circlePos),
			glm::dot(box->GetLocalY(), circlePos));
		if (localPos.y < h2 && localPos.y > -h2) {
			if (localPos.x > 0 && localPos.x < w2 + sphere->GetRadius()) {
				numContacts++;
				contact += glm::vec2(w2, localPos.y);
				direction = new glm::vec2(box->GetLocalX());
			}
			if (localPos.x < 0 && localPos.x > -(w2 + sphere->GetRadius())) {
				numContacts++;
				contact += glm::vec2(-w2, localPos.y);
				direction = new glm::vec2(-box->GetLocalX());
			}
		}
		if (localPos.x < w2 && localPos.x > -w2)
		{
			if (localPos.y > 0 && localPos.y < h2 + sphere->GetRadius())
			{
				numContacts++;
				contact += glm::vec2(localPos.x, h2);
				direction = new glm::vec2(box->GetLocalY());
			}
			if (localPos.y < 0 && localPos.y > -(h2 + sphere->GetRadius()))
			{
				numContacts++;
				contact += glm::vec2(localPos.x, -h2);
				direction = new glm::vec2(-box->GetLocalY());
			}
			
			
		}
		if (numContacts > 0)
		{
			// average, and convert back into world coords
			contact = box->GetPosition() + (1.0f / numContacts) * (box->GetLocalX() * contact.x + box->GetLocalY() * contact.y);
			box->ResolveCollision(sphere, contact, direction);
			float pen = sphere->GetRadius() - glm::length(contact - sphere->GetPosition());
			glm::vec2 norm = glm::normalize(sphere->GetPosition() - contact);
			ApplyContactForces(box, sphere, norm, pen);
		}
		delete direction;
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
	OOB* box1 = dynamic_cast<OOB*>(obj1);
	OOB* box2 = dynamic_cast<OOB*>(obj2);
	if (box1 != nullptr && box2 != nullptr) {
		glm::vec2 boxPos = box2->GetCenter() - box1->GetCenter();
		glm::vec2 norm(0, 0);
		glm::vec2 contact(0, 0);
		float pen = 0;
		int numContacts = 0;
		box1->CheckBoxCorners(*box2, contact, numContacts, pen, norm);
		if (box2->CheckBoxCorners(*box1, contact, numContacts, pen, norm)) 
		{
			norm = -norm;
		}
		if (pen > 0) {
			box1->ResolveCollision(box2, contact / float(numContacts), &norm);
			ApplyContactForces(box1, box2, norm, pen);
		}
		return true;
	}
	return false;
}

//-----------------------------------------------------------
// Applies contact force seperation to objects
//	inBody1 (Rigidbody*): What is first object?
//	inBody2 (Rigidbody*): What is second object?
//	inNorm (glm::vec2): What is the normal between objects?
//	inPen (glm::vec2) : How much is the penetration?
//-----------------------------------------------------------
void PhysicsScene::ApplyContactForces(Rigidbody* inBody1, Rigidbody* inBody2, glm::vec2 inNorm, float inPen)
{
	// if both kinematic
	if (inBody1->IsKinematic() && inBody2->IsKinematic())
	{
		return;
	}
	// if first is kinematic
	else if (inBody1->IsKinematic())
	{
		inBody2->SetPosition(inBody2->GetPosition() + 1.0f * inNorm * inPen);
	}
	// if second is kinematic
	else if (inBody2->IsKinematic())
	{
		inBody1->SetPosition(inBody1->GetPosition() + -1.0f * inNorm * inPen);
	}
	// if neither is kinematic
	else
	{
		inBody1->SetPosition(inBody1->GetPosition() + -0.5f * inNorm * inPen);
		inBody2->SetPosition(inBody2->GetPosition() + 0.5f * inNorm * inPen);
	}
}
