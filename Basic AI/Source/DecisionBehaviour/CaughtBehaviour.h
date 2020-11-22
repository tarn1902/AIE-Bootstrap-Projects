/*----------------------------------------
File Name: CaughtBehaviour.h
Purpose: Class Caught Behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "BehaviourTree.h"
class CaughtBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Caugh tBehaviour
// agent (Agent*): What will conditions be based on?
//-----------------------------------------------------------
	CaughtBehaviour(Agent* agent);
//-----------------------------------------------------------
// Destructs Caught Behaviour
//-----------------------------------------------------------
	~CaughtBehaviour();
//-----------------------------------------------------------
// Updates decision behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
	BehaviourTree* behaviour;
};

