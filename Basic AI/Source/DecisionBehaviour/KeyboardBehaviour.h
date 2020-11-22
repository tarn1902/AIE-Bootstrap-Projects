/*----------------------------------------
File Name: KeyboardBehaviour.h
Purpose: Class for using Keyboard behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Behaviour.h"
class KeyboardBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs keyboard Behaviour
//-----------------------------------------------------------
	KeyboardBehaviour();
//-----------------------------------------------------------
// Destructs keyboard Behaviour
//-----------------------------------------------------------
	virtual ~KeyboardBehaviour();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
};

