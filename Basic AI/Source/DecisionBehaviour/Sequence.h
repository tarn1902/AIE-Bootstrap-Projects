/*----------------------------------------
File Name: Sequence.h
Purpose: Class for selecting behaviour in
decision tree.
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Composite.h"
class Sequence : public Composite
{
public:
//-----------------------------------------------------------
// Constructs Sequence
//-----------------------------------------------------------
	Sequence();
//-----------------------------------------------------------
// Destructs Sequence
//-----------------------------------------------------------
	virtual ~Sequence();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime) override;
};

