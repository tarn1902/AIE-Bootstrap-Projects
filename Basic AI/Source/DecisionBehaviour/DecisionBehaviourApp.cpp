/*----------------------------------------
File Name: DecisionBehaviourApp.cpp
Purpose: Functions for DecisionBehaviourApp
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "DecisionBehaviourApp.h"
#include "CuriousBehaviour.h"
#include "CaughtBehaviour.h"
#include "AnnoyingBehaviour.h"
#include "RecruitBehaviour.h"
#include "KeyboardBehaviour.h"
#include "Box.h"
#include "Circle.h"
#include "Texture.h"
#include "Font.h"
#include <time.h>
#include "Input.h"

//Does nothing
DecisionBehaviourApp::DecisionBehaviourApp() {

}

//Does nothing
DecisionBehaviourApp::~DecisionBehaviourApp() {

}

//Sets up all points and lists of items to be used in scene
bool DecisionBehaviourApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_player = new Agent();
	m_player->AddBehaviour(new KeyboardBehaviour());
	m_player->SetPosition(Vector2(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f));

	for (int i = 0; i < 10; i++)
	{
		Box* box = new Box();
		box->minPos = Vector2((float)(rand() % 1280), (float)(rand() % 720));
		box->lengthX = 20;
		box->lengthY = 20;
		box->maxPos = Vector2(box->minPos.x + box->lengthX, box->minPos.y + box->lengthY);
		box->maxRadius = sqrt(box->lengthX * box->lengthX + box->lengthY * box->lengthY);
		objects.push_back(box);

		Circle* circle = new Circle();
		circle->Center = Vector2((float)(rand() % 1280), (float)(rand() % 720));
		circle->radius = 20;
		objects.push_back(circle);
	}
	for (int i = 0; i < 10; i++)
	{
		Agent* agent = new Agent();
		agent->SetTarget(m_player);
		agent->SetPosition(Vector2(Vector2((float)(rand() % 1280), (float)(rand() % 720))));
		agent->SetObjects(objects);
		agents.push_back(agent);
	}

	for each (Agent* agent in agents)
	{
		agent->SetAgents(agents);
	}

	return true;
}

//Deletes all pointers that have been used
void DecisionBehaviourApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	for each (Object* object in objects)
	{
		delete object;
	}
	for each (Agent* agent in agents)
	{
		delete agent;
	}
}

//Checks input to add diffrent behaviour to agents and updates agents afterwards
void DecisionBehaviourApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	if (input->wasKeyPressed(aie::INPUT_KEY_1))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new CuriousBehaviour(m_player));
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_2))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new CaughtBehaviour(m_player));
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_3))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new AnnoyingBehaviour(m_player));
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_4))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new RecruitBehaviour(m_player));
		}
	}
	m_player->Update(deltaTime);
	for each (Agent* agent in agents)
	{
		agent->Update(deltaTime);
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//Draws agents and objects in scene
void DecisionBehaviourApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	m_player->Draw(m_2dRenderer);
	for each (Agent* agent in agents)
	{
		agent->Draw(m_2dRenderer);
	}
	// draw your stuff here!
	for each (Object* object in objects)
	{
		if (static_cast<Circle*>(object)->shape == 'C')
		{
			Circle* circle = static_cast<Circle*>(object);
			m_2dRenderer->drawCircle(circle->Center.x, circle->Center.y, circle->radius);
		}
		else if (static_cast<Box*>(object)->shape == 'B')
		{
			Box* box = static_cast<Box*>(object);
			m_2dRenderer->drawBox(box->minPos.x, box->minPos.y, box->lengthX, box->lengthY);
		}
	}
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}