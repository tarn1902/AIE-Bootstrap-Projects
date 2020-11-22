/*----------------------------------------
File Name: BehaviourTree.cpp
Purpose: Functions for BehaviourTree
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "BehaviourTree.h"


//Does nothing
BehaviourTree::BehaviourTree()
{

}

//Does nothing
BehaviourTree::~BehaviourTree()
{
}
//Updates tree starting from root
bool BehaviourTree::execute(GameObject* agent, float deltaTime)
{
	return root->execute(agent, deltaTime);
}
