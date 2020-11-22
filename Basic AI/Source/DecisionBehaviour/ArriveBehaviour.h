/*----------------------------------------
File Name: ArriveBehaviour.h
Purpose: Class for using arrival behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Behaviour.h"
class ArriveBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Arrive Behaviour
//-----------------------------------------------------------
	ArriveBehaviour();
//-----------------------------------------------------------
// Destructs Arrive Behaviour
//-----------------------------------------------------------
	virtual ~ArriveBehaviour();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
};

