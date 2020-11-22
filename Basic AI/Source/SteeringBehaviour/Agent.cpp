/*----------------------------------------
File Name: Agent.cpp
Purpose: Functions for Agent
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "Renderer2D.h"
#include "Behaviour.h"
#include "Agent.h"
typedef Vec2<float> Vector2;

//Does nothing
Agent::Agent()
{
}

//Does nothing
Agent::~Agent()
{
}

//Loops through behaviours and adds velcoity to position
void Agent::Update(float deltaTime)
{
	for each (auto behaviour in m_BehaviourList)
	{
		behaviour->Update(this, deltaTime);
	}
	m_Position += m_Velocity * deltaTime;
};

//Draws a box at set position
void Agent::Draw(aie::Renderer2D* renderer)
{
	renderer->drawBox(m_Position.x, m_Position.y, 10, 10);
};

//Adds behaviour to list
void Agent::AddBehaviour(Behaviour* behaviour)
{
	m_BehaviourList.push_back(behaviour);
}

//removes all behaviours from lsit
void Agent::RemoveBehaviours()
{
	m_BehaviourList.clear();
}

//Sets position of agent
void Agent::SetPosition(Vector2 position) 
{
	m_Position = position;
}

//gets position of agent
Vector2 Agent::GetPosition()
{ 
	return m_Position; 
}

//sets velocity of agent
void Agent::SetVelocity(Vector2 velocity) 
{ 
	m_Velocity = velocity; 
}

//gets velocity of agent
Vector2 Agent::GetVelocity()
{
	return m_Velocity; 
}

//sets list of agents to agent
void Agent::SetAgents(std::vector<Agent*> inAgents)
{ 
	agents = inAgents; 
}

//gets list of agents from agent
std::vector<Agent*>  Agent::getAgents()
{ 
	return agents; 
}

//sets list of objects to agent
void Agent::SetObjects(std::vector<Object*> inObjects)
{ 
	objects = inObjects; 
}

//gets list of objects from agent
std::vector<Object*> Agent::getObjects()
{ 
	return objects; 
}

//set target of agent for behaviour
void Agent::SetTarget(Agent* agent)
{ 
	m_target = agent; 
}

//gets target of agent
Agent* Agent::GetTarget()
{ 
	return m_target;
}
