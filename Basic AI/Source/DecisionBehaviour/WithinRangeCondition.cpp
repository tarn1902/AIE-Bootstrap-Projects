/*----------------------------------------
File Name: WanderBehaviour.cpp
Purpose: Functions for WanderBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "WithinRangeCondition.h"

//Sets target and range
WithinRangeCondition::WithinRangeCondition(Agent* target, float range)
{
	m_target = target; 
	m_range = range;
}

//does nothing
WithinRangeCondition::~WithinRangeCondition()
{
}

//Tests if target is in range
bool WithinRangeCondition::Update(Agent* agent, float deltaTime) {
	// get target position 
	float tx = m_target->GetPosition().x, ty = m_target->GetPosition().y;
	// get my position 
	float x = agent->GetPosition().x, y = agent->GetPosition().y;
	// compare the two and get the distance between them 
	float xDiff = tx - x;
	float yDiff = ty - y;
	float distance = sqrtf(xDiff * xDiff + yDiff * yDiff);
	return distance <= m_range;
}
