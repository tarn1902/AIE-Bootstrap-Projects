/*----------------------------------------
File Name: WanderBehaviour.h
Purpose: Class for using wander behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Behaviour.h"
class WanderBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs wander Behaviour
//-----------------------------------------------------------
	WanderBehaviour();
//-----------------------------------------------------------
// destructs wander Behaviour
//-----------------------------------------------------------
	virtual ~WanderBehaviour();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
	float wanderAngle = 0;
};

