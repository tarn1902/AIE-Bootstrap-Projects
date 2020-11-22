/*----------------------------------------
File Name: AIProjectApp.cpp
Purpose: function for AIProjectApp
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "AIProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <algorithm>
#include <iostream>

//does nothing
AIProjectApp::AIProjectApp() {

}

//does nothing
AIProjectApp::~AIProjectApp() {

}

//Sets up grid and player information
bool AIProjectApp::startup() {

	m_2dRenderer = new aie::Renderer2D();
	player = new Agent();
	grid = new Grid();

	//set player start location
	player->SetStartNode(grid->GetNode(DEFAULT_INDEX));

	//Creates level
	grid->CreateLevel();
	agents.push_back(player);
	selectedNode = grid->GetNode(DEFAULT_INDEX);
	
	

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

//Deletes any pointers in heap
void AIProjectApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete grid;
	delete player;
}

//Updates player position to endNode and get inputs
void AIProjectApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();
	player->Update(deltaTime);

		//highlight node that mouse is hovering over
		for each (Node* node in grid->GetGrid())
		{
			selectedNode = grid->HighlightNode(node, input, selectedNode);
		}

		//Handles player Input
		//player->PlayerInputs(input, /*upNode, downNode, leftNode, rightNode,*/ selectedNode);
		if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_LEFT))
		{
			player->SetEndNode(selectedNode);
			player->ClearPath();
			player->AStar();

		}

		if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_MIDDLE))
		{
			grid->CreateBlock(selectedNode);
			selectedNode = grid->GetNode(0);
		}
		// exit the application
		if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
			quit();
}

//Draws player and grid on screen
void AIProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	grid->drawGrid(m_2dRenderer);
	player->Draw(m_2dRenderer);
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}