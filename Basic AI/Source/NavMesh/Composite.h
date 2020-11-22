/*----------------------------------------
File Name: Composite.h
Purpose: Class to be used as base in
decision tree.
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "NavMesh.h"
class Composite : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Composite
//-----------------------------------------------------------
	Composite();
//-----------------------------------------------------------
// Destructs Composite
//-----------------------------------------------------------
	~Composite();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool execute(GameObject* agent, float deltaTime) = 0;
	std::vector<Behaviour*> children;
};

