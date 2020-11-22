/*----------------------------------------
File Name: PursueBehaviour.h
Purpose: Class for using pursue behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Behaviour.h"
class PursueBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Pursue Behaviour
//-----------------------------------------------------------
	PursueBehaviour();
//-----------------------------------------------------------
// Destructs Pursue Behaviour
//-----------------------------------------------------------
	virtual ~PursueBehaviour();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
};

