/*----------------------------------------
File Name: ArriveBehaviour.h
Purpose: Class for using arrival behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Agent.h"
#include "Behaviour.h"
class Condition : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Condition
//-----------------------------------------------------------
	Condition();
//-----------------------------------------------------------
// Destructs Condition
//-----------------------------------------------------------
	virtual ~Condition();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime) = 0;
};

