/*----------------------------------------
File Name: WanderBehaviour.cpp
Purpose: Functions for WanderBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "WanderBehaviour.h"
#include "Agent.h"

//does nothing
WanderBehaviour::WanderBehaviour()
{
}

//does nothing
WanderBehaviour::~WanderBehaviour()
{
}

//each update, wander angle is to change direction slightly
bool WanderBehaviour::Update(Agent* agent, float deltaTime) {
	Vector2 circleCenter = agent->GetVelocity();
	Vector2 displacement = Vector2(0, -1);
	// what you want to do is this: generate a random number between -0.5 and 0.5
	// then multiple this number by ANGLE_CHANGE
	// ANGLE_CHANGE should be a number (less than PI/2)
	//wanderAngle += (rand() * ANGLE_CHANGE) - (ANGLE_CHANGE * .5);
	wanderAngle += ((rand() / 32768.f - 0.5f) * 0.3f);
	displacement *= (float)(CIRCLE_RADIUS);
	displacement = Vector2(cosf(wanderAngle)*displacement.x - sinf(wanderAngle)*displacement.y, sinf(wanderAngle)*displacement.x + cosf(wanderAngle)*displacement.y);
	agent->SetVelocity(agent->GetVelocity() + (((circleCenter + displacement).normalised() * (float)(MAX_SPEED)) - agent->GetVelocity()) * deltaTime);
	return true;
};
