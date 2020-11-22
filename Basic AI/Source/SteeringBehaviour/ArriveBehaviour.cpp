/*----------------------------------------
File Name: ArriveBehaviour.cpp
Purpose: Functions for ArriveBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "ArriveBehaviour.h"
#include "Agent.h"

//does nothing
ArriveBehaviour::ArriveBehaviour()
{
}

//does nothing
ArriveBehaviour::~ArriveBehaviour()
{
}

//Gets direction by comparing the two positions of agents and reduces it by comparing to radius
bool ArriveBehaviour::Update(Agent* agent, float deltaTime) {
	if (agent->GetTarget() == nullptr)
		return false;
	Vector2 agentPos = agent->GetPosition();
	Vector2 targetPos = agent->GetTarget()->GetPosition();
	Vector2 direction = (targetPos - agentPos);
	direction.normalise();
	agent->SetVelocity(agent->GetVelocity() + (((direction * (float)MAX_SPEED) - agent->GetVelocity()) * agentPos.distance(targetPos) / (float)CIRCLE_RADIUS) * deltaTime);
	return true;

};
