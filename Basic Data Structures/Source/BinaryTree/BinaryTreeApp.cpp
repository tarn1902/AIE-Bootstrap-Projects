/*----------------------------------------
File Name: BinaryTreeApp.cpp
Purpose: Holds each method for BinaryTreeApp.h
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "BinaryTreeApp.h"


//-----------------------------------------------------------
// Constructs Application
//-----------------------------------------------------------
BinaryTreeApp::BinaryTreeApp() 
{
	
}

//-----------------------------------------------------------
// Destroys Application
//-----------------------------------------------------------
BinaryTreeApp::~BinaryTreeApp() {

}

//-----------------------------------------------------------
// Creates pointers to created objects for application
//	return (bool): returns true if method is run correctly
//-----------------------------------------------------------
bool BinaryTreeApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("../../../../bin/font/consolas.ttf", 32);
	return true;

}

//-----------------------------------------------------------
// Deletes pointers of created objects
//-----------------------------------------------------------
void BinaryTreeApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

//-----------------------------------------------------------
// Checks any updates related to inputs
//	deltaTime (float): what time was it called?
//-----------------------------------------------------------
void BinaryTreeApp::update(float deltaTime) {

	aie::Input* input = aie::Input::getInstance();
	static int value = 0;
	ImGui::InputInt("Value", &value);
	if (ImGui::Button("Insert", ImVec2(50, 0)))
	{
		m_binaryTree.Insert(value);
		m_selectedNode = m_binaryTree.Find(value);
	}
	if (ImGui::Button("Remove", ImVec2(50, 0)))
	{
		m_binaryTree.Remove(value);
	}
	if (ImGui::Button("Find", ImVec2(50, 0)))
	{
		m_selectedNode = m_binaryTree.Find(value);
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//-----------------------------------------------------------
// Draws text or objects to window
//-----------------------------------------------------------
void BinaryTreeApp::draw() {

	// wipe the screen to the background colour
	clearScreen();
	// begin drawing sprites
	m_2dRenderer->begin();
	// draw your stuff here!
	m_binaryTree.draw(m_2dRenderer, m_selectedNode, m_font);
	// output some text
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	// done drawing sprites
	m_2dRenderer->end();

}