/*----------------------------------------
File Name: DynamicArrayApp.cpp
Purpose: Holds each method for DynamicArrayApp.h
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/

#include "DynamicArrayApp.h"

//-----------------------------------------------------------
// Constructs Application
//-----------------------------------------------------------
DynamicArrayApp::DynamicArrayApp() {

}

//-----------------------------------------------------------
// Destroys Application
//-----------------------------------------------------------
DynamicArrayApp::~DynamicArrayApp() {

}


//-----------------------------------------------------------
// Creates pointers to created objects for application
//	return (bool): returns true if method is run correctly
//-----------------------------------------------------------
bool DynamicArrayApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../../../../bin/font/consolas.ttf", 32);
	array.CreateArray(2);
	return true;
}

//-----------------------------------------------------------
// Deletes pointers of created objects
//-----------------------------------------------------------
void DynamicArrayApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

//-----------------------------------------------------------
// Checks any updates related to inputs
//	deltaTime (float): what time was it called?
//-----------------------------------------------------------
void DynamicArrayApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();
	static int value = 0;
	ImGui::InputInt("Value", &value);
	if (ImGui::Button("Add To Start", ImVec2(150, 0)))
	{
		array.AddToStart(value);
		highLight = -1;
	}
	if (ImGui::Button("Add To Middle", ImVec2(150, 0)))
	{
		array.AddToMid(value);
		highLight = -1;
	}
	if (ImGui::Button("Add To End", ImVec2(150, 0)))
	{
		array.AddToEnd(value);
		highLight = -1;
	}
	if (ImGui::Button("Remove From Start", ImVec2(150, 0)))
	{
		array.RemoveFromStart();
		highLight = -1;
	}  
	if (ImGui::Button("Remove From Middle", ImVec2(150, 0)))
	{
		array.RemoveFromMid();
		highLight = -1;
	}
	if (ImGui::Button("Remove From End", ImVec2(150, 0)))
	{
		array.RemoveFromEnd();
		highLight = -1;
	}
	if (ImGui::Button("Reduce Space", ImVec2(150, 0)))
	{
		array.ReduceSpace();
		highLight = -1;
	}
	if (ImGui::Button("Binary Search", ImVec2(150, 0)))
	{
		highLight = array.BinarySearch(value);
	}
	if (ImGui::Button("Linear Search", ImVec2(150, 0)))
	{
		highLight = array.LinearSearch(value);
	}
	if (ImGui::Button("Bubble Sort", ImVec2(150, 0)))
	{
		array.BubbleSort();
		highLight = -1;
	}
	if (ImGui::Button("Insertion Sort", ImVec2(150, 0)))
	{
		array.InsertionSort();
		highLight = -1;
	}
	if (ImGui::Button("Clear", ImVec2(150, 0)))
	{
		array.Clear();
		highLight = -1;
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();


}

//-----------------------------------------------------------
// Draws text or objects to window
//-----------------------------------------------------------
void DynamicArrayApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	float spacingX = 0;
	float spacingY = 0;
	spacingX = 1280 / float(array.allocatedvalues+1);
	float xPos = spacingX;
	spacingY = 720 / 2;
	for (int i = 0; i < array.allocatedvalues; i++)
	{
		float yPos = 720 / 2;
		static char buffer[20];
		sprintf_s(buffer, "%d", array.data[i]);
		if (i == highLight)
		{
			m_2dRenderer->setRenderColour(255, 0, 0);
			m_2dRenderer->drawBox(xPos, yPos, 60+10, 60+10);
		}
		m_2dRenderer->setRenderColour(255, 255, 255);
		m_2dRenderer->drawBox(xPos, yPos, 60, 60);
		if (i < array.usedElements)
		{
			m_2dRenderer->setRenderColour(0, 0, 0);
			m_2dRenderer->drawText(m_font, buffer, xPos - 10, yPos - 10);
		}
		xPos += spacingX;
	}

	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}