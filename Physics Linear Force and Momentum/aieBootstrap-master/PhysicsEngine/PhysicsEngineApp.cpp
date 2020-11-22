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
	gravity[0] = 0;
	gravity[1] = 0;
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
}

//-----------------------------------------------------------
// Check inputs to Change and create new scenes
// inDeltaTime (float): What is time since last update
//-----------------------------------------------------------
void PhysicsEngineApp::update(float inDeltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	ImGui::Begin("Settings");
	//Creates basic scene demostrating projectile having a set intial velocity and being pulled by gravity
	if (ImGui::Button("Scene 1"))
	{
		CreateScene1();
	}
	//Creates basic scene demostrating two objects with same velocity, but able to have diffrent mass moving away from each other
	else if (ImGui::Button("Scene 2"))
	{
		CreateScene2();
	}
	//Creates basic scene demostrating two objects with same velocity, but able to have diffrent mass colliding with eachother. This does not work perfectly without more physics calculations
	else if (ImGui::Button("Scene 3"))
	{
		CreateScene3();
	}
	//Creates scene simulating a rocket launch
	else if (ImGui::Button("Scene 4"))
	{
		CreateScene4();
	}
	//If shows gravity
	if (!scene2 && !scene3)
	{
		if (ImGui::InputFloat2("Gravity", gravity))
		{
			ResetScene();
		}
	}
	if (ImGui::InputFloat("Mass of Object 1", &mass1))
	{
		ResetScene();
	}
	//If shows mass 2
	if (!scene1)
	{
		if (ImGui::InputFloat("Mass of Object 2", &mass2))
		{
			ResetScene();
		}
	}
	
	//If runs rocket scene
	if (scene4)
	{
		if (ImGui::InputFloat("Force of ejection", &force))
		{
			ResetScene();
		}
		if (rocket->GetMass() > 1)
		{
			if (flightTime >= 0.1)
			{
				rocket->SetMass(rocket->GetMass() - mass2);
				Sphere* fuel = new Sphere(rocket->GetPosition() - glm::vec2(0, mass1 + mass2 + 2), glm::vec2(0, 0), mass2, mass2, glm::vec4(0, 1, 0, 1));
				physicsScene->AddActor(fuel);
				fuel->ApplyForceToActor(rocket, glm::vec2(0, force/mass2));
				flightTime = 0;
			}
			else
			{
				flightTime += inDeltaTime;
			}
		}
		
	}
	ImGui::End();
	aie::Gizmos::clear();
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
// Creates Scene 1
//-----------------------------------------------------------
void PhysicsEngineApp::CreateScene1()
{
	delete physicsScene;
	scene1 = true;
	scene2 = false;
	scene3 = false;
	scene4 = false;

	physicsScene = new PhysicsScene();
	physicsScene->SetGravity(glm::vec2(gravity[0], gravity[1]));
	physicsScene->SetTimeStep(0.01f);
	Sphere* ball;
	ball = new Sphere(glm::vec2(-40, 0), glm::vec2(10, 30), mass1, 1, glm::vec4(1, 0, 0, 1));
	physicsScene->AddActor(ball);
}

//-----------------------------------------------------------
// Creates Scene 2
//-----------------------------------------------------------
void PhysicsEngineApp::CreateScene2()
{
	delete physicsScene;
	scene1 = false;
	scene2 = true;
	scene3 = false;
	scene4 = false;

	physicsScene = new PhysicsScene();
	physicsScene->SetGravity(glm::vec2(0, 0));
	Sphere* ball1 = new Sphere(glm::vec2(-4, 0), glm::vec2(0, 0), mass1, 4, glm::vec4(1, 0, 0, 1));
	Sphere* ball2 = new Sphere(glm::vec2(4, 0), glm::vec2(0, 0), mass2, 4, glm::vec4(0, 1, 0, 1));
	physicsScene->AddActor(ball1);
	physicsScene->AddActor(ball2);
	ball1->ApplyForceToActor(ball2, glm::vec2(2, 0));
}

//-----------------------------------------------------------
// Creates Scene 3
//-----------------------------------------------------------
void PhysicsEngineApp::CreateScene3()
{
	delete physicsScene;
	scene1 = false;
	scene2 = false;
	scene3 = true;
	scene4 = false;

	physicsScene = new PhysicsScene();
	physicsScene->SetGravity(glm::vec2(gravity[0], gravity[1]));
	physicsScene->SetTimeStep(0.01f);
	Sphere* ball1 = new Sphere(glm::vec2(-20, 0), glm::vec2(0, 0), mass1, 4, glm::vec4(1, 0, 0, 1));
	Sphere* ball2 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), mass2, 4, glm::vec4(0, 1, 0, 1));
	physicsScene->AddActor(ball1);
	physicsScene->AddActor(ball2);
	ball1->ApplyForce(glm::vec2(30, 0));
	ball2->ApplyForce(glm::vec2(-15, 0));
}

//-----------------------------------------------------------
// Creates Scene 4
//-----------------------------------------------------------
void PhysicsEngineApp::CreateScene4()
{
	delete physicsScene;
	scene1 = false;
	scene2 = false;
	scene3 = false;
	scene4 = true;

	physicsScene = new PhysicsScene();
	physicsScene->SetGravity(glm::vec2(gravity[0], gravity[1]));
	physicsScene->SetTimeStep(0.01f);
	rocket = new Sphere(glm::vec2(0, 0), glm::vec2(0, 0), mass1, mass1, glm::vec4(1, 0, 0, 1));
	physicsScene->AddActor(rocket);
}

//-----------------------------------------------------------
// Resets current scene
//-----------------------------------------------------------
void PhysicsEngineApp::ResetScene()
{
	if (scene1)
	{
		CreateScene1();
	}
	else if (scene2)
	{
		CreateScene2();
	}
	else if (scene3)
	{
		CreateScene3();
	}
	else
	{
		CreateScene4();
	}
}
