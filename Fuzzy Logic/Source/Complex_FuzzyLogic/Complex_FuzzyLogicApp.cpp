/*----------------------------------------
File Name: Complex_FuzzyLogicApp.cpp
Purpose: Holds functions for application
Author: Tarn Cooper
Modified: 07 June 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Complex_FuzzyLogicApp.h"
#include "Font.h"
#include "Input.h"
#include "SimulationObjects.h"

Fuzzy Complex_FuzzyLogicApp::m_fuzzyEngine;

//-----------------------------------------------------------
// Empty Constructor
//-----------------------------------------------------------
Complex_FuzzyLogicApp::Complex_FuzzyLogicApp() {

}

//-----------------------------------------------------------
// Empty Destructor
//-----------------------------------------------------------
Complex_FuzzyLogicApp::~Complex_FuzzyLogicApp() {

}

//-----------------------------------------------------------
// Starts up app by populating world and setting membership 
// functions
//-----------------------------------------------------------
bool Complex_FuzzyLogicApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("./font/consolas.ttf", 32);


	//set up simulation world.
	m_worldController = new WorldController();
	for (int i = 0; i < 1; i++)
	{
		Agent* simpleAI = new Agent(glm::vec2(rand() % 1000, rand() % 500));
		m_worldController->addObject(simpleAI);
	}
	
	for (int i = 0; i < 1; i++)
	{
		AgentPred* predAI = new AgentPred(glm::vec2(rand() % 1000, rand() % 500));
		m_worldController->addObject(predAI);
	}
	
	for (int i = 0; i < 1; i++)
	{
		Water* water1 = new Water(glm::vec2(rand() % 1000, rand() % 500));
		m_worldController->addObject(water1);
	}

	for (int i = 0; i < 1; i++)
	{
		Cave* cave = new Cave(glm::vec2(rand() % 1000, rand() % 500));
		m_worldController->addObject(cave);
	}

	for (int i = 0; i < 1; i++)
	{
		Food* food = new Food(glm::vec2(rand() % 1000, rand() % 500));
		m_worldController->addObject(food);
	}

	//the following code sets up all the membership functions for the fuzzy sets

	//membership functions for the tiredess set
	m_fuzzyEngine.tired = new leftShoulderMembershipFunction(0.2f, 0.4f, "tired");
	m_fuzzyEngine.awake = new TrapezoidFunction(0.2f, 0.4f, 0.6f, 0.8f, "awake");
	m_fuzzyEngine.superActive = new rightShoulderMembershipFunction(0.6f, 0.8f, "SuperActive");

	//membership functions for the hunger set
	m_fuzzyEngine.veryHungry = new leftShoulderMembershipFunction(0.2f, 0.4f, "very hungry");
	m_fuzzyEngine.hungry = new TrapezoidFunction(.2f, .4f, .8f, .9f, "hungry");
	m_fuzzyEngine.full = new rightShoulderMembershipFunction(.8f, .9f, "full");

	//membership functions for the thirst set
	m_fuzzyEngine.WeekFromThirsty = new leftShoulderMembershipFunction(0.1f, 0.3f, "week from thirst");
	m_fuzzyEngine.veryThirsty = new TriangleFunction(0.1f, 0.3f, 0.5f, "very thristy");
	m_fuzzyEngine.thirsty = new TriangleFunction(0.3f, 0.5f, 0.7f, "thristy");
	m_fuzzyEngine.notThirsty = new rightShoulderMembershipFunction(.5f, .7f, "not thirsty");

	//membership functions for the distance set
	m_fuzzyEngine.veryNear = new leftShoulderMembershipFunction(2, 4, "very close");
	m_fuzzyEngine.mediumRange = new TrapezoidFunction(2, 4, 50, 70, "medium range");
	m_fuzzyEngine.farAway = new rightShoulderMembershipFunction(50, 70, "far away");

	//membership functions for the desirability set (used for defuzification)
	m_fuzzyEngine.undesirable = new leftShoulderMembershipFunction(0.3f, 0.5f, "undesirable");
	m_fuzzyEngine.desirable = new TriangleFunction(0.3f, 0.5f, 0.7f, "desirable");
	m_fuzzyEngine.veryDesirable = new rightShoulderMembershipFunction(0.5f, 0.7f, "very desirable");

	return true;
}

//-----------------------------------------------------------
// deletes pointers
//-----------------------------------------------------------
void Complex_FuzzyLogicApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete m_worldController;
}

//-----------------------------------------------------------
// Updates input and world controller
// deltaTime (float): How long since last frame?
//-----------------------------------------------------------
void Complex_FuzzyLogicApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_worldController->update(deltaTime);

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//-----------------------------------------------------------
// Draws objects on screen
//-----------------------------------------------------------
void Complex_FuzzyLogicApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_worldController->draw(m_2dRenderer);

	// output some text
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}