/*----------------------------------------
File Name: SoundProgramming.cpp
Purpose: class of SoundProgramming
Author: Tarn Cooper
Modified: 27 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>
#include "FlyCamera.h"
//Sound Programming class
class SoundProgramming : public aie::Application {
public:

	SoundProgramming();
	virtual ~SoundProgramming();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	FMOD::System* pFmodSystem = NULL;
	FMOD::Sound* pBackgroundSound;
	FMOD_RESULT result;
	FMOD::Channel* pBackgroundChannel;
	bool played = false;
	FlyCamera* camera;
	FMOD::Sound* pEnviroSound1;
	FMOD::Sound* pEnviroSound2;
	FMOD::Sound* pShotSound;
	FMOD::Channel* pEnviroChannel1;
	FMOD::Channel* pEnviroChannel2;
	FMOD::Channel* pShotChannel;
};