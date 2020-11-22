/*----------------------------------------
File Name: PhysicsEngineApp.cpp
Purpose: Runs application
Author: Tarn Cooper
Modified: 06 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "PhysicsEngineApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <Gizmos.h>
#include <imgui.h>
//-----------------------------------------------------------
// Constructs PhysicsEngineApp
//-----------------------------------------------------------
PhysicsEngineApp::PhysicsEngineApp() {

}
//-----------------------------------------------------------
// Destructs PhysicsEngineApp
//-----------------------------------------------------------
PhysicsEngineApp::~PhysicsEngineApp() {

}
//-----------------------------------------------------------
// Starts up app
// return (bool): Returns true if started correctly
//-----------------------------------------------------------
bool PhysicsEngineApp::startup() {
	
	// increase the 2d line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("./font/consolas.ttf", 32);
	physicsScene = new PhysicsScene;

	Box* box1 = new Box(glm::vec2(-10, 20), glm::vec2(10, 0), 1, glm::vec2(1, 1), glm::vec4(1, 1, 1, 1));
	Sphere* sphere1 = new Sphere(glm::vec2(0, 20), glm::vec2(0, 0), 1, 1, glm::vec4(1, 1, 1, 1));
	physicsScene->AddActor(box1);
	physicsScene->AddActor(sphere1);

	Sphere* sphere2 = new Sphere(glm::vec2(-10, 10), glm::vec2(10, 0), 1, 1, glm::vec4(1, 1, 1, 1));
	Box* box2 = new Box(glm::vec2(0, 10), glm::vec2(0, 0), 1, glm::vec2(1, 1), glm::vec4(1, 1, 1, 1));
	physicsScene->AddActor(box2);
	physicsScene->AddActor(sphere2);

	Box* box3 = new Box(glm::vec2(0, 0), glm::vec2(10, 0), 1, glm::vec2(1, 1), glm::vec4(1, 1, 1, 1));
	Sphere* sphere3 = new Sphere(glm::vec2(0, -10), glm::vec2(10, 0), 1, 1, glm::vec4(1, 1, 1, 1));
	Plane* plane = new Plane(glm::vec2(-1, 0), -20);
	physicsScene->AddActor(box3);
	physicsScene->AddActor(sphere3);
	physicsScene->AddActor(plane);

	Box* box4 = new Box(glm::vec2(0, -20), glm::vec2(10, 0), 1, glm::vec2(1, 1), glm::vec4(1, 1, 1, 1));
	Box* box5 = new Box(glm::vec2(10, -20), glm::vec2(0, 0), 1, glm::vec2(1, 1), glm::vec4(1, 1, 1, 1));
	physicsScene->AddActor(box4);
	physicsScene->AddActor(box5); 
	
	Sphere* sphere4 = new Sphere(glm::vec2(0, -30), glm::vec2(10, 0), 1, 1, glm::vec4(1, 1, 1, 1));
	Sphere* sphere5 = new Sphere(glm::vec2(10, -30), glm::vec2(0, 0), 1, 1, glm::vec4(1, 1, 1, 1));
	physicsScene->AddActor(sphere4);
	physicsScene->AddActor(sphere5);

	return true;

}

//-----------------------------------------------------------
// Shutdown app
//-----------------------------------------------------------
void PhysicsEngineApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete physicsScene;
}

//-----------------------------------------------------------
// Check inputs
// inDeltaTime (float): What is time since last update
//-----------------------------------------------------------
void PhysicsEngineApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	

	aie::Gizmos::clear();
	physicsScene->Update(deltaTime);
	physicsScene->UpdateGizmos();
		
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//-----------------------------------------------------------
// Draws objects into scene
//-----------------------------------------------------------
void PhysicsEngineApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}
