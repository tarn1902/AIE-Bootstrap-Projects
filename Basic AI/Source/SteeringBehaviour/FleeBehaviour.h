/*----------------------------------------
File Name: FleeBehaviour.h
Purpose: Class for using fleebehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Behaviour.h"
class FleeBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Flee Behaviour
//-----------------------------------------------------------
	FleeBehaviour();
//-----------------------------------------------------------
// Destructor Flee Behaviour
//-----------------------------------------------------------
	virtual ~FleeBehaviour();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
};

