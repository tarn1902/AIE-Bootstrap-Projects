/*----------------------------------------
File Name: Selector.h
Purpose: Class to select specfic behaviour
in decision tree.
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Composite.h"
class Selector : public Composite
{
public:
//-----------------------------------------------------------
// Constructs Selector
//-----------------------------------------------------------
	Selector();
//-----------------------------------------------------------
// Destructs Selector
//-----------------------------------------------------------
	virtual ~Selector();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime) override;
};

