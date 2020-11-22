/*----------------------------------------
File Name: EvadeBehaviour.cpp
Purpose: Functions for EvadeBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "FleeBehaviour.h"
#include "Agent.h"

//Does nothing
FleeBehaviour::FleeBehaviour()
{
}

//Does nothing
FleeBehaviour::~FleeBehaviour()
{
}

//makes velocity of agent doing away from targets position
bool FleeBehaviour::Update(Agent* agent, float deltaTime) {
	if (agent->GetTarget() == nullptr)
		return false;
	Vector2 agentPos = agent->GetPosition();
	Vector2 targetPos = agent->GetTarget()->GetPosition();
	Vector2 direction = (agentPos - targetPos);
	direction.normalise();
	agent->SetVelocity(agent->GetVelocity() + ((direction * (float)MAX_SPEED) - agent->GetVelocity()) * deltaTime);
	return true;

};
