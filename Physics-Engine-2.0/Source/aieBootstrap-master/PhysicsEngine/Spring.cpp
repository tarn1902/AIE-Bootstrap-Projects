/*----------------------------------------
File Name: Spring.cpp
Purpose:  Acts as a sphere joint of two objects in physics scene
Author: Tarn Cooper
Modified: 08 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Spring.h"
#include <Gizmos.h>

//-----------------------------------------------------------
// Construct Spring
//	inBody1 (Rigidbody*): What is first joint attachment?
//	inBody2 (Rigidbody*): What is second joint attachment?
//	inRestLength (float): What is the rest length of joint?
//	inSpringCoef (float): What is the spring coefficient of joint?
//	inDamping (float): What is the damping of joint?
//	inContact1 (glm::vec2): What is first contact point?
//	inContact2 (glm::vec2): What is second contact point?
//-----------------------------------------------------------
Spring::Spring(Rigidbody* inBody1, Rigidbody* inBody2, float inRestLength, float inSpringCoef, float inDamping, glm::vec2 inContact1, glm::vec2 inContact2) : Rigidbody(JOINT, glm::vec2(0,0), glm::vec2(0,0), 0, 1)
{
	body1 = inBody1;
	body2 = inBody2;
	restLength = inRestLength;
	springCoef = inSpringCoef;
	damping = inDamping;
	contact1 = inContact1;
	contact2 = inContact2;
}

//-----------------------------------------------------------
// Destruct Spring
//-----------------------------------------------------------
Spring::~Spring()
{

}

//-----------------------------------------------------------
// Creates visuals of object
//-----------------------------------------------------------
void Spring::MakeGizmo()
{
	aie::Gizmos::add2DLine(body1->GetPosition(), body2->GetPosition(), colour);
}

//-----------------------------------------------------------
// Updates object with spring force
// inGravity (glm::vec2): What is the gravity on this object?
// inTimeStep (glm::vec2): What is the current time step?
//-----------------------------------------------------------
void Spring::FixedUpdate(glm::vec2 inGravity, float inTimeStep)
{
	glm::vec2 p2 = body2->ToWorld();
	glm::vec2 p1 = body1->ToWorld();
	glm::vec2 dist = p2 - p1;
	float length = sqrtf(dist.x * dist.x + dist.y * dist.y);

	// apply damping
	glm::vec2 relativeVelocity = body2->GetVelocity() - body1->GetVelocity();

	// F = -kX - bv
	glm::vec2 force = dist * springCoef * (restLength - length) - damping * relativeVelocity;

	body1->ApplyForce(-force * inTimeStep, p1 - body1->GetPosition());
	body2->ApplyForce(force * inTimeStep, p2 - body2->GetPosition());

}