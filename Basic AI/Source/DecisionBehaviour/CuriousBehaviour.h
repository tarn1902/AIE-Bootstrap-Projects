/*----------------------------------------
File Name: CuriousBehaviour.h
Purpose: Class for using annoying behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "BehaviourTree.h"
class CuriousBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Curious Behaviour
// agent (Agent*): What will conditions be based on?
//-----------------------------------------------------------
	CuriousBehaviour(Agent* agent);
//-----------------------------------------------------------
// Destructs Curious Behaviour
//-----------------------------------------------------------
	virtual ~CuriousBehaviour();
//-----------------------------------------------------------
// Updates decision behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
	BehaviourTree* behaviour;
};

