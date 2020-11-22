/*----------------------------------------
File Name: SeekBehaviour.h
Purpose: Class for using seek behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Behaviour.h"
class SeekBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Seek Behaviour
//-----------------------------------------------------------
	SeekBehaviour();
//-----------------------------------------------------------
// Destructs Seek Behaviour
//-----------------------------------------------------------
	virtual ~SeekBehaviour();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
};

