#pragma once
/*----------------------------------------
File Name: WithinRangeCondition.h
Purpose: Condition behaviour for decision
tree to test if within a range of target
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "Agent.h"
#include "Condition.h"
class WithinRangeCondition : public Condition
{
public:
//-----------------------------------------------------------
// Constructs Within range Condition
//-----------------------------------------------------------
	WithinRangeCondition(Agent* target, float range);
//-----------------------------------------------------------
// destructs Within range Condition
//-----------------------------------------------------------
	virtual ~WithinRangeCondition();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime) override;
private:
	Agent* m_target;
	float m_range;
};

