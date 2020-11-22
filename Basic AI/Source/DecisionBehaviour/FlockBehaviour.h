/*----------------------------------------
File Name: FlockBehaviour.h
Purpose: Class for using flock behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Behaviour.h"
class FlockBehaviour : public Behaviour
{
public:
//-----------------------------------------------------------
// Constructs Flock Behaviour
//-----------------------------------------------------------
	FlockBehaviour();
//-----------------------------------------------------------
// Destructs Flock Behaviour
//-----------------------------------------------------------
	virtual ~FlockBehaviour();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime);

private:
//-----------------------------------------------------------
// Figures out alignment force needed
// agent (Agent*): What is current agent?
// Return (Vector2): gets alignment force
//-----------------------------------------------------------
	Vector2 AlignmentForce(Agent* agent);
//-----------------------------------------------------------
// Figures out Cohesion force needed
// agent (Agent*): What is current agent?
// Return (Vector2): gets Cohesion force
//-----------------------------------------------------------
	Vector2 CohesionForce(Agent* agent);
//-----------------------------------------------------------
// Figures out Seperation force needed
// agent (Agent*): What is current agent?
// Return (Vector2): gets Seperation force
//-----------------------------------------------------------
	Vector2 SeperationForce(Agent* agent);

	int seperationWeight = 100;
	int allignmentWeight = 100;
	int cohesionWeight = 100;
	int neighbourCount = 0;
};

