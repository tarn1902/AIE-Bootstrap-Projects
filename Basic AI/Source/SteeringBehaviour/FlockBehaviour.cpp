/*----------------------------------------
File Name: FlockBehaviour.cpp
Purpose: Functions for FlockBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "FlockBehaviour.h"
#include "Agent.h"

//Does nothing
FlockBehaviour::FlockBehaviour()
{
}

//Does nothing
FlockBehaviour::~FlockBehaviour()
{
}

//Sets velocity to the combined force os seperation, cohesion and alignment
bool FlockBehaviour::Update(Agent* agent, float deltaTime)
{
	Vector2 seperate = SeperationForce(agent);
	Vector2 cohesion = CohesionForce(agent);
	Vector2 alignment = AlignmentForce(agent);
	neighbourCount = 0;
	agent->SetVelocity(agent->GetVelocity() + ((cohesion + seperate + alignment) - agent->GetVelocity()) * deltaTime);
	return true;
};

//Gets average force of all agents near by returns that
Vector2 FlockBehaviour::AlignmentForce(Agent* agent)
{
	Vector2 forceToApply = Vector2();
	for each (Agent* otherAgent in agent->getAgents())
	{
		if (otherAgent != agent)
		{
			if ((otherAgent->GetPosition() - agent->GetPosition()).magnitude() < 100)
			{
				forceToApply.x += otherAgent->GetVelocity().x;
				forceToApply.y += otherAgent->GetVelocity().y;
				neighbourCount++;
			}
		}
	}
	if (neighbourCount == 0)
	{
		return forceToApply;
	}

	forceToApply.x /= neighbourCount;
	forceToApply.y /= neighbourCount;
	forceToApply.normalise();
	neighbourCount = 0;
	return (forceToApply)* (float)allignmentWeight;
}

//Gets average force towards all neighbours and returns that
Vector2 FlockBehaviour::CohesionForce(Agent* agent)
{
	Vector2 forceToApply = Vector2();
	for each (Agent* otherAgent in agent->getAgents())
	{
		if (otherAgent != agent)
		{
			if ((otherAgent->GetPosition() - agent->GetPosition()).magnitude() < 100)
			{
				forceToApply.x += otherAgent->GetPosition().x - agent->GetPosition().x;
				forceToApply.y += otherAgent->GetPosition().y - agent->GetPosition().y;
				neighbourCount++;
			}
		}
	}
	if (neighbourCount == 0)
	{
		return forceToApply;
	}

	forceToApply.x /= neighbourCount;
	forceToApply.y /= neighbourCount;
	forceToApply.normalise();
	neighbourCount = 0;
	return forceToApply * (float)cohesionWeight;
}

//Gets average force away from all neighbours and returns that
Vector2 FlockBehaviour::SeperationForce(Agent* agent)
{
	Vector2 forceToApply = Vector2();
	for each (Agent* otherAgent in agent->getAgents())
	{
		if (otherAgent != agent)
		{
			if ((otherAgent->GetPosition() - agent->GetPosition()).magnitude() < 100)
			{
				forceToApply.x += agent->GetPosition().x - otherAgent->GetPosition().x;
				forceToApply.y += agent->GetPosition().y - otherAgent->GetPosition().y;
				neighbourCount++;
			}
		}
	}
	if (neighbourCount == 0)
	{
		return forceToApply;
	}

	forceToApply.x /= neighbourCount;
	forceToApply.y /= neighbourCount;
	forceToApply.normalise();
	neighbourCount = 0;
	return (forceToApply)* (float)seperationWeight;
}
