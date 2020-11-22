/*----------------------------------------
File Name: HashingApp.h
Purpose: Controls how the application behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "HashingApp.h"

//-----------------------------------------------------------
// Constructs Application
//-----------------------------------------------------------
HashingApp::HashingApp() {

}
//-----------------------------------------------------------
// Destroys Application
//-----------------------------------------------------------
HashingApp::~HashingApp() {

}

//-----------------------------------------------------------
// Creates pointers to created objects for application
//	return (bool): returns true if method is run correctly
//-----------------------------------------------------------
bool HashingApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	hashTable["car.png"] = new aie::Texture("../../../../bin/textures/car.png");
	hashTable["rock_Large.png"] = new aie::Texture("../../../../bin/textures/rock_Large.png");
	hashTable["ship.png"] = new aie::Texture("../../../../bin/textures/ship.png");
	hashTable["ball.png"] = new aie::Texture("../../../../bin/textures/ball.png");
	list[0] = "car.png";
	list[1] = "rock_Large.png";
	list[2] = "ship.png";
	list[3] = "ball.png";
	m_font = new aie::Font("../../../../bin/font/consolas.ttf", 32);
	return true;
}
\
//-----------------------------------------------------------
// Deletes pointers of created objects
//-----------------------------------------------------------
void HashingApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

//-----------------------------------------------------------
// Checks any updates related to inputs
//	deltaTime (float): what time was it called?
//-----------------------------------------------------------
void HashingApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
	if (input->wasKeyPressed(aie::INPUT_KEY_LEFT))
	{
		selection--;
		if (selection == -1)
		{
			selection = 3;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_RIGHT))
	{	
		selection++;
		if (selection == 4)
		{
			selection = 0;
		}
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//-----------------------------------------------------------
// Draws text or objects to window
//-----------------------------------------------------------
void HashingApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_2dRenderer->drawSprite(hashTable[list[selection]], 1280/2, 720/2, 60, 60);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, list[selection], 0, 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}
