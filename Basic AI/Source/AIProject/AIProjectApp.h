/*----------------------------------------
File Name: AIProjectApp.h
Purpose: Class for app
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Grid.h"
#include "Agent.h"

class AIProjectApp : public aie::Application {
public:
//-----------------------------------------------------------
// Constructs app
//-----------------------------------------------------------
	AIProjectApp();
//-----------------------------------------------------------
// Destructs app
//-----------------------------------------------------------
	virtual ~AIProjectApp();
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
	Grid*				grid;
	Node*				selectedNode;
	Agent*				player;
	std::vector<Agent*>  agents;
	const int DEFAULT_INDEX = 120;
};