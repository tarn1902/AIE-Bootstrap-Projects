/*----------------------------------------
File Name: CuriousBehaviour.cpp
Purpose: Functions for CuriousBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "CuriousBehaviour.h"
#include "Sequence.h"
#include "Selector.h"
#include "WanderBehaviour.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "WithinRangeCondition.h"
#include "CollisionAvoidBehaviour.h"


//Constructs behaviour tree to be curious
CuriousBehaviour::CuriousBehaviour(Agent* agent)
{
	Sequence* fleeSequence = new Sequence();
	fleeSequence->children.push_back(new WithinRangeCondition(agent, 100));
	fleeSequence->children.push_back(new FleeBehaviour());

	Sequence* seekSequence = new Sequence();
	seekSequence->children.push_back(new WithinRangeCondition(agent, 300));
	seekSequence->children.push_back(new SeekBehaviour());

	Sequence* wanderSequence = new Sequence();
	wanderSequence->children.push_back(new WanderBehaviour());

	Selector* movementSelect = new Selector();
	movementSelect->children.push_back(fleeSequence);
	movementSelect->children.push_back(seekSequence);
	movementSelect->children.push_back(wanderSequence);

	Selector* avoidSequence = new Selector();
	avoidSequence->children.push_back(new CollisionAvoidBehaviour());
	avoidSequence->children.push_back(movementSelect);
	

	behaviour = new BehaviourTree();
	behaviour->root = avoidSequence;
}

//deletes behaviour
CuriousBehaviour::~CuriousBehaviour()
{
	delete behaviour;
}

//updates behaviour starting from root
bool CuriousBehaviour::Update(Agent* agent, float deltaTime)
{
	behaviour->root->Update(agent, deltaTime);
	return true;
}
