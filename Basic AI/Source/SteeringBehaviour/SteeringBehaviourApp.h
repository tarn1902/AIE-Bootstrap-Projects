/*----------------------------------------
File Name: SteeringBehaviourApp.h
Purpose: Class for running app
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Agent.h"
#include "Object.h"
class Agent;

class SteeringBehaviourApp : public aie::Application {
public:
//-----------------------------------------------------------
// Constructs app
//-----------------------------------------------------------
	SteeringBehaviourApp();
//-----------------------------------------------------------
// Destructs app
//-----------------------------------------------------------
	virtual ~SteeringBehaviourApp();
//-----------------------------------------------------------
// starts up app
// return (bool): returns if worked
//-----------------------------------------------------------
	virtual bool startup();
//-----------------------------------------------------------
// shuts down app
// return (bool): returns if worked
//-----------------------------------------------------------
	virtual void shutdown();
//-----------------------------------------------------------
// Updates app
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual void update(float deltaTime);
//-----------------------------------------------------------
// Draws app
//-----------------------------------------------------------
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Agent*				m_player; 
	std::vector<Object*> objects;
	std::vector<Agent*> agents;
	bool objectsVisible = false;
};