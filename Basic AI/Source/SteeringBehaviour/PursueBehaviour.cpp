/*----------------------------------------
File Name: PursueBehaviour.cpp
Purpose: Functions for PursueBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "PursueBehaviour.h"
#include "Agent.h"

//Does nothing
PursueBehaviour::PursueBehaviour()
{
}

//Does nothing
PursueBehaviour::~PursueBehaviour()
{
}

//Sets velocity to go towards direction of targets direction
bool PursueBehaviour::Update(Agent* agent, float deltaTime) {
	if (agent->GetTarget() == nullptr)
	{
		return false;
	}
		
	Vector2 agentPos = agent->GetPosition();
	Vector2 targetPos = agent->GetTarget()->GetPosition() + agent->GetTarget()->GetVelocity();
	Vector2 direction = (targetPos - agentPos);
	direction.normalise();
	agent->SetVelocity(agent->GetVelocity() + ((direction * (float)MAX_SPEED) - agent->GetVelocity()) * deltaTime);
	return true;

};
