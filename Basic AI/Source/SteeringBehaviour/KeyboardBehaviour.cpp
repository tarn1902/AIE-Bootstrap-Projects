/*----------------------------------------
File Name: KeyboardBehaviour.cpp
Purpose: Functions for KeyboardBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "KeyboardBehaviour.h"
#include "Input.h"
#include "Agent.h"


//Does nothing
KeyboardBehaviour::KeyboardBehaviour()
{
}

//Does nothing
KeyboardBehaviour::~KeyboardBehaviour()
{
}

//Sets velocity depending on which direction button was pressed
bool KeyboardBehaviour::Update(Agent* agent, float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	if (input->isKeyDown(aie::INPUT_KEY_UP)) agent->SetVelocity(agent->GetVelocity() + Vector2(0, 500.0f) * deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_DOWN)) agent->SetVelocity(agent->GetVelocity() + Vector2(0, -500.0f)* deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_LEFT)) agent->SetVelocity(agent->GetVelocity() + Vector2(-500.0f, 0)* deltaTime);
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT)) agent->SetVelocity(agent->GetVelocity() + Vector2(500.0f, 0)* deltaTime);
	return true;
};
