/*----------------------------------------
File Name: BehaviourTree.h
Purpose: Class holding root of behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Composite.h"
 class BehaviourTree : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Behaviour Tree
//-----------------------------------------------------------
	BehaviourTree();
//-----------------------------------------------------------
// Destructs Behaviour Tree
//-----------------------------------------------------------
	virtual ~BehaviourTree();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool execute(GameObject* agent, float deltaTime) override;
	Composite* root = nullptr;
};

