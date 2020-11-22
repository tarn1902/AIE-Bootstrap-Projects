/*----------------------------------------
File Name: Behaviour.h
Purpose: Class for holding consts and
virtual functions.
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
class Agent;

template <typename T>
class Vec2;

class Behaviour
{
public:
	typedef Vec2<float> Vector2;
//-----------------------------------------------------------
// Constructs Behaviour
//-----------------------------------------------------------
	Behaviour();
//-----------------------------------------------------------
// Destructs Behaviour
//-----------------------------------------------------------
	virtual ~Behaviour();
//-----------------------------------------------------------
// Updates behaviour
// agent (Agent*): What is current agent?
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual bool Update(Agent* agent, float deltaTime) = 0;
protected:
	const int MAX_SPEED = 500;
	const int CIRCLE_RADIUS = 100;
	const int ANGLE_CHANGE = 100;
	const float MAX_SEE_AHEAD = 50;
	const int MAX_AVOID_FORCE = 100;
};

