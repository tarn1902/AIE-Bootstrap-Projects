/*----------------------------------------
File Name: CollisionAvoidBehaviour.cpp
Purpose: Functions for CollisionAvoidBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "CollisionAvoidBehaviour.h"
#include "Circle.h"
#include "Box.h"
#include "Agent.h"

//Does nothing
CollisionAvoidBehaviour::CollisionAvoidBehaviour()
{

}

//Does nothing
CollisionAvoidBehaviour::~CollisionAvoidBehaviour()
{
}

//updates agent through collisionAvoid function
bool CollisionAvoidBehaviour::Update(Agent* agent, float deltaTime)
{
	
	return collisionAvoid(agent, deltaTime);
};

//Test if threat is there then calcualtes force to avoid it
bool CollisionAvoidBehaviour::collisionAvoid(Agent* agent, float deltaTime)
{

	Vector2 ahead = agent->GetPosition() + agent->GetVelocity().normalised() * MAX_SEE_AHEAD;
	Vector2 ahead2 = ahead * 0.5;

	Object* mostThreat = findMostThreat(agent, ahead, ahead2);
	Vector2 avoidance = Vector2(0, 0);

	if (mostThreat != nullptr)
	{
		if (static_cast<Circle*>(mostThreat)->shape == 'C')
		{
			Circle* circleThreat = static_cast<Circle*>(mostThreat);
			avoidance = ahead - circleThreat->Center;
			avoidance.normalise();
			avoidance = (avoidance * (float)MAX_AVOID_FORCE) - agent->GetVelocity();
		}
		else if (static_cast<Box*>(mostThreat)->shape == 'B')
		{
			Box* boxThreat = static_cast<Box*>(mostThreat);
			avoidance = ahead - Vector2(boxThreat->minPos.x + boxThreat->lengthX/2, boxThreat->minPos.y + boxThreat->lengthY / 2);
			avoidance.normalise();
			avoidance = (avoidance * (float)MAX_AVOID_FORCE) - agent->GetVelocity();
		}
		agent->SetVelocity(agent->GetVelocity() + avoidance * deltaTime);
	}
	else
	{
		return false;
	}

	return true;
}

//See if there is threat incoming, if muliple finds closest
Object* CollisionAvoidBehaviour::findMostThreat(Agent* agent, Vector2 ahead, Vector2 ahead2)
{
	Object* mostThreat = nullptr;

	for each (Object* threat in agent->getObjects())
	{
		if (static_cast<Circle*>(threat)->shape == 'C')
		{
			Circle* circleThreat = static_cast<Circle*>(threat);
			if (LineIntersectsCircle(ahead, ahead2, threat) && (mostThreat == nullptr || agent->GetPosition().distance(circleThreat->Center) < agent->GetPosition().distance(circleThreat->Center)))
			{
				mostThreat = threat;
			}
		}
		else if (static_cast<Box*>(threat)->shape == 'B')
		{
			Box* boxThreat = static_cast<Box*>(threat);
			if (LineIntersectsCircle(ahead, ahead2, threat) && (mostThreat == nullptr || agent->GetPosition().distance(Vector2(boxThreat->minPos.x + boxThreat->lengthX / 2, boxThreat->minPos.y + boxThreat->lengthY / 2)) < agent->GetPosition().distance(Vector2(boxThreat->minPos.x + boxThreat->lengthX / 2, boxThreat->minPos.y + boxThreat->lengthY / 2))))
			{
				mostThreat = threat;
			}
		}
		
	}
	return mostThreat;
}

//Test if line intersects with object
bool CollisionAvoidBehaviour::LineIntersectsCircle(Vector2 ahead, Vector2 ahead2, Object* obstacle)
{
	if (obstacle != nullptr)
	{
		if (static_cast<Circle*>(obstacle)->shape == 'C')
		{
			Circle* circleObstacle = static_cast<Circle*>(obstacle);
			if (circleObstacle->Center.distance(ahead) <= circleObstacle->radius || circleObstacle->Center.distance(ahead2) <= circleObstacle->radius)
			{
				return true;
			}
		}
		else if (static_cast<Box*>(obstacle)->shape == 'B')
		{
			Box* boxObstacle = static_cast<Box*>(obstacle);
			if (Vector2(boxObstacle->minPos.x + boxObstacle->lengthX / 2, boxObstacle->minPos.y + boxObstacle->lengthY / 2).distance(ahead) <= boxObstacle->maxRadius || Vector2(boxObstacle->minPos.x + boxObstacle->lengthX / 2, boxObstacle->minPos.y + boxObstacle->lengthY / 2).distance(ahead2) <= boxObstacle->maxRadius)
			{
				return true;
			}
		}
	}
	return false;
}
