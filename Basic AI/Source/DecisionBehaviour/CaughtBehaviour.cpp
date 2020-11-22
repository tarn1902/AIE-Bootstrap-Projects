/*----------------------------------------
File Name: CaughtBehaviour.cpp
Purpose: Functions for Box
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "CaughtBehaviour.h"
#include "Sequence.h"
#include "Selector.h"
#include "WanderBehaviour.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "WithinRangeCondition.h"
#include "CollisionAvoidBehaviour.h"

//Creates behaviour tree with goal of running away till caught.
CaughtBehaviour::CaughtBehaviour(Agent* agent)
{
	Sequence* fleeSequence = new Sequence();
	fleeSequence->children.push_back(new WithinRangeCondition(agent, 300));
	fleeSequence->children.push_back(new FleeBehaviour());

	Sequence* seekSequence = new Sequence();
	seekSequence->children.push_back(new WithinRangeCondition(agent, 100));
	seekSequence->children.push_back(new SeekBehaviour());

	Sequence* wanderSequence = new Sequence();
	wanderSequence->children.push_back(new WanderBehaviour());

	Selector* movementSelect = new Selector();
	movementSelect->children.push_back(seekSequence);
	movementSelect->children.push_back(fleeSequence);
	movementSelect->children.push_back(wanderSequence);

	Selector* avoidSequence = new Selector();
	avoidSequence->children.push_back(new CollisionAvoidBehaviour());
	avoidSequence->children.push_back(movementSelect);
	

	behaviour = new BehaviourTree();
	behaviour->root = avoidSequence;
}

//Deletes beahviour
CaughtBehaviour::~CaughtBehaviour()
{
	delete behaviour;
}

//Updates starting from root
bool CaughtBehaviour::Update(Agent* agent, float deltaTime)
{
	behaviour->root->Update(agent, deltaTime);
	return true;
}
