/*----------------------------------------
File Name: CollisionAvoidBehaviour.h
Purpose: Class for using CollisionAvoidBehaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Behaviour.h"
class Object;
class CollisionAvoidBehaviour: public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Collision Avoid Behaviour
//-----------------------------------------------------------
	CollisionAvoidBehaviour();
//-----------------------------------------------------------
// Destructs Collision Avoid Behaviour
//-----------------------------------------------------------
	virtual ~CollisionAvoidBehaviour();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);
//-----------------------------------------------------------
// Used to avoid objects in scene
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
// return (bool): Returns if attempted to avoid object
//-----------------------------------------------------------
	bool collisionAvoid(Agent* agent, float deltaTime);

private:
//-----------------------------------------------------------
// Finds most threatning object in line of sight
// agent (Agent*): What is current agent?
// ahead (Vector2): What is first line ahead?
// ahead (Vector2): What is second line ahead?
// return (Object*): Returns object it needs to avoid
//-----------------------------------------------------------
	Object* findMostThreat(Agent* agent, Vector2 ahead, Vector2 ahead2);
//-----------------------------------------------------------
// Checks if line intesects object
// ahead (Vector2): What is first line ahead?
// ahead (Vector2): What is second line ahead?
// obstacle (Object*): What objects can it run into?
// return (bool): If agent is in sight of object
//-----------------------------------------------------------
	bool LineIntersectsCircle(Vector2 ahead, Vector2 ahead2, Object* obstacle);
};

