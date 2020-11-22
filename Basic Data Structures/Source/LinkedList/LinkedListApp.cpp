/*----------------------------------------
File Name: LinkedListApp.cpp
Purpose: Holds each method for LinkedListApp.h
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "LinkedListApp.h"

//-----------------------------------------------------------
// Constructs Application
//-----------------------------------------------------------
LinkedListApp::LinkedListApp() {

}

//-----------------------------------------------------------
// Destroys Application
//-----------------------------------------------------------
LinkedListApp::~LinkedListApp() {

}

//-----------------------------------------------------------
// Creates pointers to created objects for application
//	return (bool): returns true if method is run correctly
//-----------------------------------------------------------
bool LinkedListApp::startup() {

	m_2dRenderer = new aie::Renderer2D();
	highLight = nullptr;
	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../../../../bin/font/consolas.ttf", 32);
	return true;
}

//-----------------------------------------------------------
// Deletes pointers of created objects
//-----------------------------------------------------------
void LinkedListApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

//-----------------------------------------------------------
// Checks any updates related to inputs
//	deltaTime (float): what time was it called?
//-----------------------------------------------------------
void LinkedListApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();
	static int value = 0;
	ImGui::InputInt("Value", &value);
	if (ImGui::Button("Push Back", ImVec2(150, 0)))
	{
		list.PushBack(value);
		highLight = nullptr;
	}
	if (ImGui::Button("Push Front", ImVec2(150, 0)))
	{
		list.PushFront(value);
		highLight = nullptr;
	}
	if (ImGui::Button("Pop Back", ImVec2(150, 0)))
	{
		list.PopBack();
		highLight = nullptr;
	}
	if (ImGui::Button("Pop Front", ImVec2(150, 0)))
	{
		list.PopFront();
		highLight = nullptr;
	}

	if (ImGui::Button("Binary Search", ImVec2(150, 0)))
	{
		highLight = list.BinarySearch(value);
	}
	if (ImGui::Button("Linear Search", ImVec2(150, 0)))
	{
		highLight = list.LinearSearch(value);
	}
	if (ImGui::Button("Bubble Sort", ImVec2(150, 0)))
	{
		list.BubbleSort();
		highLight = nullptr;
	}
	if (ImGui::Button("Insertion Sort", ImVec2(150, 0)))
	{
		list.InsertionSort();
		highLight = nullptr;
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();


}

//-----------------------------------------------------------
// Draws text or objects to window
//-----------------------------------------------------------
void LinkedListApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	float spacingX = 0;
	float spacingY = 0;
	spacingX = 1280 / (float)(list.Count()+1);
	float xPos = spacingX;
	spacingY = 720 / 2;
	ListNode<int>* currentNode = list.Begin();
	while (currentNode != nullptr)
	{
		float yPos = 720 / 2;
		static char buffer[10];
		sprintf_s(buffer, "%d", currentNode->data);
		if (currentNode == highLight)
		{
			m_2dRenderer->setRenderColour(255, 0, 0);
			m_2dRenderer->drawBox(xPos, yPos, 60 + 10, 60 + 10);
		}
		m_2dRenderer->setRenderColour(255, 255, 255);
		m_2dRenderer->drawBox(xPos, yPos, 60, 60);
		m_2dRenderer->setRenderColour(0, 0, 0);
		m_2dRenderer->drawText(m_font, buffer, xPos - 10, yPos - 10);
		xPos += spacingX;
		currentNode = currentNode->next;
	}
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}