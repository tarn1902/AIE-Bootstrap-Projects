/*----------------------------------------
File Name: Selector.cpp
Purpose: Functions for Selector
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "Selector.h"


//does nothing
Selector::Selector()
{
}

//does nothing
Selector::~Selector()
{

}

//goes through list of behaviours till something returns true
bool Selector::execute(GameObject* agent, float deltaTime)
{
	bool test = false;
	for each (Behaviour* child in children)
	{
		test = child->execute(agent, deltaTime);
		if (test)
			return test;
	}
	return false;
}
