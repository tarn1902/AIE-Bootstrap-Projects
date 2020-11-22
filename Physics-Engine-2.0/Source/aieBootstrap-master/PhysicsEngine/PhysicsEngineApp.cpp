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
#include <Gizmos.h>
#include <imgui.h>
#include "OOB.h"
#include "Spring.h"
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
	physicsScene = new PhysicsScene();
	SetRadiosToFalse();
	gravity[0] = 0;
	gravity[1] = -10;
	startPos[0] = 0;
	startPos[1] = 0;
	*mass = 0;
	startVel[0] = 0;
	startVel[1] = 0;
	*radius = 0;
	colour[0] = 0;
	colour[1] = 0;
	colour[2] = 0;
	colour[3] = 0;
	extents[0] = 0;
	extents[1] = 0;
	*springCof = 0;
	*damping = 0;
	*restLength = 0;
	normal[0] = 0;
	normal[1] = 0;
	*distance = 0;
	*isStatic = false;

	physicsScene->SetGravity(glm::vec2(gravity[0], gravity[1]));
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
	delete mass;
	delete startVel;
	delete radius;
	delete colour;
	delete extents;
	delete isObject;
	delete springCof;
	delete damping;
	delete restLength;
	delete normal;
	delete distance;
	delete isStatic;
}

//-----------------------------------------------------------
// Check inputs
// inDeltaTime (float): What is time since last update
//-----------------------------------------------------------
void PhysicsEngineApp::update(float inDeltaTime) 
{
	//All possible options for object spawner
	ImGui::Begin("Object Spawner");
	//Select Object type
	if (ImGui::RadioButton("Sphere", isObject[0]))
	{
		SetRadiosToFalse();
		isObject[0] = true;
	}
	if (ImGui::RadioButton("Box", isObject[1]))
	{
		SetRadiosToFalse();
		isObject[1] = true;
	}
	if (ImGui::RadioButton("Joint", isObject[2]))
	{
		SetRadiosToFalse();
		isObject[2] = true;
	}
	if (ImGui::RadioButton("Plane", isObject[3]))
	{
		SetRadiosToFalse();
		isObject[3] = true;
	}

	//if a solid object
	if (isObject[0] || isObject[1])
	{
		ImGui::InputFloat2("Position", startPos);
		ImGui::InputFloat2("Velocity", startVel);
		ImGui::InputFloat("Mass", mass);
		ImGui::Checkbox("Static", isStatic);
		if (isObject[0])
		{
			ImGui::InputFloat("Radius", radius);
		}
		if (isObject[1])
		{
			ImGui::InputFloat2("Extents", extents);
		}
	}
	
	//if a joint
	if (isObject[2])
	{
		ImGui::InputFloat("Rest Length", restLength);
		ImGui::InputFloat("Spring Coeficient", springCof);
		ImGui::InputFloat("Damping", damping);
	}

	// if a plane
	if (isObject[3])
	{
		ImGui::InputFloat2("Normal", normal);
		ImGui::InputFloat("Distance", distance);
	}

	ImGui::InputFloat4("Colour", colour);

	//Allows to pause and play simulation
	if (!isPaused)
	{
		if (ImGui::Button("Pause"))
		{
			isPaused = true;
		}
	}
	else
	{
		if (ImGui::Button("Play"))
		{
			isPaused = false;
		}
	}
	
	ImGui::End();

	aie::Input* input = aie::Input::getInstance();
	
	std::vector<PhysicsObject*> actors = physicsScene->GetActors();

	//actor exists can do these
	if (actors.size() != 0)
	{
		ChangeSelected(input, actors[selected], actors);

		//Deletes object from scene
		if (input->wasKeyPressed(aie::INPUT_KEY_DELETE))
		{
			physicsScene->RemoveActor(actors[selected]);
			selected = 0;
		}

		
		//tags object in scene as alternative
		if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
		{
			selectedAlt = selected;
			selected = 0;
			actors[selectedAlt]->SetColour(glm::vec4(1, 0, 1, 1));
		}
	}

	//Inserts object into scene
	if (input->wasKeyPressed(aie::INPUT_KEY_INSERT))
	{
		if (isObject[0])
		{
			Sphere* sphere = new Sphere(glm::vec2(startPos[0], startPos[1]), glm::vec2(startVel[0], startVel[1]), *mass, *radius, glm::vec4(colour[0], colour[1], colour[2], colour[3]));
			sphere->SetKinematic(*isStatic);
			physicsScene->AddActor(sphere);
		}

		if (isObject[1])
		{
			OOB* oob = new OOB(glm::vec2(startPos[0], startPos[1]), glm::vec2(startVel[0], startVel[1]), *mass, glm::vec2(extents[0], extents[1]), glm::vec4(colour[0], colour[1], colour[2], colour[3]));
			oob->SetKinematic(*isStatic);
			physicsScene->AddActor(oob);
		}

		if (isObject[2])
		{
			Spring* spring = new Spring(dynamic_cast<Rigidbody*>(actors[selected]), dynamic_cast<Rigidbody*>(actors[selectedAlt]), *restLength, *springCof, *damping);
			spring->SetColour(glm::vec4(colour[0], colour[1], colour[2], colour[3]));
			physicsScene->AddActor(spring);

		}

		if (isObject[3])
		{
			Plane* plane = new Plane(glm::vec2(normal[0], normal[1]), *distance);
			plane->SetColour(glm::vec4(colour[0], colour[1], colour[2], colour[3]));
			physicsScene->AddActor(plane);
		}
	}
	
	aie::Gizmos::clear();
	physicsScene->UpdateGizmos();
	//if not paused
	if (!isPaused)
	{
		physicsScene->Update(inDeltaTime);
	}
	
		
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
// Allows to select object with arrows
//	inInput (aie::Input*): How to control input?
//	inObject (aie::Input*): What is current object?
//	inActors (std::vector<PhysicsObject*>): What are all the objects in scene?
// return (int): Returns the score of the specified player.
//-----------------------------------------------------------
void PhysicsEngineApp::ChangeSelected(aie::Input* inInput, PhysicsObject* inObject, std::vector<PhysicsObject*> inActors)
{
	//if right arrow pressed
	if (inInput->wasKeyPressed(aie::INPUT_KEY_RIGHT))
	{
		if (selected == selectedAlt)
		{
			inObject->SetColour(glm::vec4(1, 0, 1, 1));
		}
		else
		{
			inObject->SetColour(glm::vec4(1, 1, 1, 1));
		}

		selected++;
		if (selected > inActors.size() - 1)
		{
			selected = 0;
		}
	}
	//if left arrow pressed
	else if (inInput->wasKeyPressed(aie::INPUT_KEY_LEFT))
	{
		if (selected == selectedAlt)
		{
			inObject->SetColour(glm::vec4(1, 0, 1, 1));
		}
		else
		{
			inObject->SetColour(glm::vec4(1, 1, 1, 1));
		}

		selected--;
		if (selected < 0)
		{
			selected = inActors.size() - 1;
		}
	}
	else
	{
		inObject->SetColour(glm::vec4(1, 1, 0, 1));
	}
}

//-----------------------------------------------------------
// Sets all radio buttons to false.
//-----------------------------------------------------------
void PhysicsEngineApp::SetRadiosToFalse()
{
	for (int i = 0; i < isObjectSize; i++)
	{
		isObject[i] = false;
	}
}
