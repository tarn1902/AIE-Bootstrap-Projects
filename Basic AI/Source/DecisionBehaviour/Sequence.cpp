/*----------------------------------------
File Name: Sequence.cpp
Purpose: Functions for Sequence
Author: Tarn Cooper  
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "Sequence.h"


//does nothing
Sequence::Sequence()
{
}

//does nothing
Sequence::~Sequence()
{
}

//Goes through list of behaviours till something is false
bool Sequence::Update(Agent* agent, float deltaTime)
{
	bool test = false;
	for each (Behaviour* child in children)
	{
		test = child->Update(agent, deltaTime);
		if (!test)
			return false;
	}
	return test;
}
