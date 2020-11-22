/*----------------------------------------
File Name: PhysicsEngineApp.cpp
Purpose: Runs application
Author: Tarn Cooper
Modified: 10 March 2020
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
	physicsScene->SetGravity(glm::vec2(0, -10));
	physicsScene->SetTimeStep(0.5f);

	startPos[0] = -40;
	startPos[1] = 0;
	gravity[0] = 0;
	gravity[1] = -10;
	*speed = 40;
	*inclination = 45;
	*timeStep = 0.5f;


	return true;

}

//-----------------------------------------------------------
// Shutsdown app
//-----------------------------------------------------------
void PhysicsEngineApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	delete physicsScene;
	delete gravity;
	delete startPos;
	delete speed;
	delete inclination;
	delete timeStep;
}

//-----------------------------------------------------------
// Check inputs
// inDeltaTime (float): What is time since last update
//-----------------------------------------------------------
void PhysicsEngineApp::update(float inDeltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
	ImGui::Begin("Settings");
	ImGui::InputFloat2("Start Position", startPos);
	ImGui::InputFloat("Speed", speed);
	ImGui::InputFloat("Inclination", inclination);
	ImGui::InputFloat("TimeStep", timeStep);
	ImGui::InputFloat("Gravity", &gravity[1]);


	if (ImGui::Button("Fire"))
	{
		physicsScene->AddActor(new Sphere(glm::vec2(startPos[0], startPos[1]), glm::vec2(cos((*inclination) * glm::pi<float>() / 180) * (*speed), sin((*inclination) * glm::pi<float>() / 180) * (*speed)), 1.0f, 1, glm::vec4(1, 0, 0, 1)));
		SetupContinousDemo(glm::vec2(startPos[0], startPos[1]),*inclination, *speed, gravity[1]);
	}
	if (ImGui::Button("Reset"))
	{
		aie::Gizmos::clear();
		physicsScene->SetGravity(glm::vec2(gravity[0], gravity[1]));
		physicsScene->SetTimeStep(*timeStep);
	}
	ImGui::End();
	
	
	physicsScene->Update(inDeltaTime);
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

//-----------------------------------------------------------
// Simulates projectile using specfic time points
//	inStartPos (aie::vec2): Where does object start?
//	inInclination (float): What incline will be used?
//	inSpeed (float): What is the speed of object?
//	inGravity (float): How strong is the gravity?
//-----------------------------------------------------------
void PhysicsEngineApp::SetupContinousDemo(glm::vec2 inStartPos, float inInclination, float inSpeed, float inGravity)
{
	float t = 0;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);
	while (t <= 5)
	{
		// calculate the x, y position of the projectile at time t
		float x = inStartPos.x + (cos(inInclination * glm::pi<float>()/180) * inSpeed) * t;
		float y = inStartPos.y + (sin(inInclination * glm::pi<float>() / 180) * inSpeed) * t + 0.5 * inGravity * (t * t);

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);
		t += *timeStep;
	}
}
