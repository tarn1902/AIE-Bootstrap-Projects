/*----------------------------------------
File Name: SoundProgramming.cpp
Purpose: Function of SoundProgramming class
Author: Tarn Cooper
Modified: 27 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "SoundProgramming.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

//-----------------------------------------------------------
// Constructs sound programming class
//-----------------------------------------------------------
SoundProgramming::SoundProgramming() {

}

//-----------------------------------------------------------
// Destructs sound programming class
//-----------------------------------------------------------
SoundProgramming::~SoundProgramming() {

}

//-----------------------------------------------------------
// Starts up class with FMOD assets
//-----------------------------------------------------------
bool SoundProgramming::startup() 
{
	//Create Camera
	camera = new FlyCamera();
	camera->SetLookAt(vec3(0, 10, 10), vec3(0), vec3(0, 1, 0));
	camera->SetPerspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.f);

	//Create FMOD system
	result = FMOD::System_Create(&pFmodSystem);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}

	//Start FMOD system
	result = pFmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}

	//Create sounds
	result = pFmodSystem->createSound("audio/background_music.ogg", FMOD_CREATESTREAM, 0, &pBackgroundSound);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}

	result = pFmodSystem->createSound("audio/evironmental_effect_01.ogg", FMOD_LOOP_NORMAL | FMOD_3D, 0, &pEnviroSound1);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}

	result = pFmodSystem->createSound("audio/environmental_effect_02.ogg", FMOD_LOOP_NORMAL | FMOD_3D, 0, &pEnviroSound2);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}

	result = pFmodSystem->createSound("audio/gunshot.ogg", FMOD_DEFAULT, 0, &pShotSound);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}

	//Play starting sounds
	result = pFmodSystem->playSound(pBackgroundSound, 0, false, &pBackgroundChannel);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}

	result = pFmodSystem->playSound(pEnviroSound1, 0, false, &pEnviroChannel1);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}

	result = pFmodSystem->playSound(pEnviroSound2, 0, false, &pEnviroChannel2);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}

	//Loops sounds
	result = pEnviroChannel1->setLoopCount(-1);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}

	result = pEnviroChannel2->setLoopCount(-1);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
	}

	//Position sounds
	FMOD_VECTOR channelPosition1 = { 10,0,0 };
	FMOD_VECTOR channelPosition2 = { -10,0,0 };
	FMOD_VECTOR channelVelocity = { 0,0,0 };

	result = pEnviroChannel1->set3DAttributes(&channelPosition1, &channelVelocity, 0);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}

	result = pEnviroChannel2->set3DAttributes(&channelPosition2, &channelVelocity, 0);
	if (result != FMOD_OK) {
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		return false;
	}



	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);


	return true;
}
//-----------------------------------------------------------
//Shutdown class and fmod sounds
//-----------------------------------------------------------
void SoundProgramming::shutdown() {

	pBackgroundSound->release();
	pEnviroSound1->release();
	pEnviroSound2->release();
	pShotSound->release();
	pFmodSystem->close();
	pFmodSystem->release();
	Gizmos::destroy();
}

//-----------------------------------------------------------
// Updates class with moving camera and triggered sounds
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
void SoundProgramming::update(float deltaTime) {
	pFmodSystem->update();


	camera->Update(deltaTime);

	//Sets up listener on camera
	glm::vec4 forwardDirection = glm::normalize(-camera->GetWorldTransform()[2]);
	glm::vec4 upDirection = glm::normalize(-camera->GetWorldTransform()[1]);
	FMOD_VECTOR position = { camera->GetWorldTransform()[3].x, camera->GetWorldTransform()[3].y, camera->GetWorldTransform()[3].z };
	FMOD_VECTOR velocity = { camera->GetCurrentSpeed().x, camera->GetCurrentSpeed().y, camera->GetCurrentSpeed().z };
	FMOD_VECTOR forward = { forwardDirection.x, forwardDirection.y, forwardDirection.z };
	FMOD_VECTOR up = { upDirection.x, upDirection.y, upDirection.z };

	pFmodSystem->set3DListenerAttributes(0, &position, &velocity, &forward, &up);

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}


	// quit if we press escape
	aie::Input * input = aie::Input::getInstance();
	//Triggers gunshot
	if (input->isMouseButtonDown(0))
	{
		pShotChannel->setPitch((float)(rand() % 10) + (rand() % 11 / 10));
		result = pFmodSystem->playSound(pShotSound, 0, false, &pShotChannel);
		if (result != FMOD_OK) {
			printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		}
	}
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//-----------------------------------------------------------
// Draws images on screen
//-----------------------------------------------------------
void SoundProgramming::draw() {

	// wipe the screen to the background colour
	clearScreen();


	Gizmos::draw(camera->GetProjectView());
}