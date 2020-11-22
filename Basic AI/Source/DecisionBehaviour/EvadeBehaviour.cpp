/*----------------------------------------
File Name: EvadeBehaviour.cpp
Purpose: Functions for EvadeBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "EvadeBehaviour.h"
#include "Agent.h"
#include "..\MathsLibrarySLL\MathsLibrarySLL.h"
typedef Vec2<float> Vector2;
//Does nothing
EvadeBehaviour::EvadeBehaviour()
{
}

//Does nothing
EvadeBehaviour::~EvadeBehaviour()
{
}

//Sets velocity of target depending on direction of target is going
bool EvadeBehaviour::Update(Agent* agent, float deltaTime) {
	if (agent->GetTarget() == nullptr)
		return false;
	Vector2 agentPos = agent->GetPosition();
	Vector2 targetPos = agent->GetTarget()->GetPosition() + agent->GetTarget()->GetVelocity();
	Vector2 direction = (agentPos - targetPos);
	direction.normalise();
	agent->SetVelocity(agent->GetVelocity() + ((direction * (float)MAX_SPEED) - agent->GetVelocity()) *deltaTime);
	return true;

};