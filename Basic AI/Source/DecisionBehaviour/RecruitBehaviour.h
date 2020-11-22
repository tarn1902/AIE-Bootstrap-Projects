/*----------------------------------------
File Name: RecruitBehaviour.h
Purpose: Class for using recruit behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "BehaviourTree.h"
class RecruitBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Recruit Behaviour
// agent (Agent*): What will conditions be based on?
//-----------------------------------------------------------
	RecruitBehaviour(Agent* agent);
//-----------------------------------------------------------
// Destructs Recruit Behaviour
//-----------------------------------------------------------	
	~RecruitBehaviour();
//-----------------------------------------------------------
// Updates decision behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
	BehaviourTree* behaviour;
};


