/*----------------------------------------
File Name: SeekBehaviour.cpp
Purpose: Functions for SeekBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "SeekBehaviour.h"
#include "Agent.h"

//does nothing
SeekBehaviour::SeekBehaviour()
{
}

//does nothing
SeekBehaviour::~SeekBehaviour()
{
}

//sets velocity to go have direction go twoards position
bool SeekBehaviour::Update(Agent* agent, float deltaTime)
{
	if (agent->GetTarget() == nullptr)
		return false;
	Vector2 agentPos = agent->GetPosition();
	Vector2 targetPos = agent->GetTarget()->GetPosition();
	Vector2 direction = (targetPos - agentPos);
	direction.normalise();
	agent->SetVelocity(agent->GetVelocity() + ((direction * (float)MAX_SPEED) - agent->GetVelocity())* deltaTime);
	return true;
};
