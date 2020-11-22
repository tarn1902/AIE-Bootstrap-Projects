/*----------------------------------------
File Name: EvadeBehaviour.h
Purpose: Class for using evade behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Behaviour.h"
class EvadeBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Evade Behaviour
//-----------------------------------------------------------
	EvadeBehaviour();
//-----------------------------------------------------------
// Destructs Evade Behaviour
//-----------------------------------------------------------
	virtual ~EvadeBehaviour();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
};

