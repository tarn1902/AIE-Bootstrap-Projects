/*----------------------------------------
File Name: Agent.cpp
Purpose: Functions for Agent
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "AnnoyingBehaviour.h"
#include "Sequence.h"
#include "Selector.h"
#include "WanderBehaviour.h"
#include "PursueBehaviour.h"
#include "EvadeBehaviour.h"
#include "WithinRangeCondition.h"
#include "CollisionAvoidBehaviour.h"


//Constructs new behaviour tree to be annoying
AnnoyingBehaviour::AnnoyingBehaviour(Agent* agent)
{
	Sequence* evadeSequence = new Sequence();
	evadeSequence->children.push_back(new WithinRangeCondition(agent, 300));
	evadeSequence->children.push_back(new EvadeBehaviour());

	Sequence* pursueSequence = new Sequence();
	pursueSequence->children.push_back(new WithinRangeCondition(agent, 600));
	pursueSequence->children.push_back(new PursueBehaviour());

	Sequence* wanderSequence = new Sequence();
	wanderSequence->children.push_back(new WanderBehaviour());

	Selector* movementSelect = new Selector();
	movementSelect->children.push_back(evadeSequence);
	movementSelect->children.push_back(pursueSequence);
	movementSelect->children.push_back(wanderSequence);

	Selector* avoidSequence = new Selector();
	avoidSequence->children.push_back(new CollisionAvoidBehaviour());
	avoidSequence->children.push_back(movementSelect);
	

	behaviour = new BehaviourTree();
	behaviour->root = avoidSequence;
}

//deletes behaviour stored
AnnoyingBehaviour::~AnnoyingBehaviour()
{
	delete behaviour;
}

//updates tree starting from root
bool AnnoyingBehaviour::Update(Agent* agent, float deltaTime)
{
	behaviour->root->Update(agent, deltaTime);
	return true;
}
