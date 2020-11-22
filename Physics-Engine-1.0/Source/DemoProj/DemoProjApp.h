/*----------------------------------------
File Name: CircleObject.h
Purpose: Handles how bootstrap runs
Author: Tarn Cooper
Modified: 13/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "SceneObject.h"

//Class for controling application
class DemoProjApp : public aie::Application {
public:
	//-----------------------------------------------------------
	// Constructs application
	//-----------------------------------------------------------
	DemoProjApp();
	//-----------------------------------------------------------
	// Destructs application
	//-----------------------------------------------------------
	virtual ~DemoProjApp();

	//-----------------------------------------------------------
	// Controls how application starts up 
	//-----------------------------------------------------------
	virtual bool startup() override;
	//-----------------------------------------------------------
	// Controls how application shuts down
	//-----------------------------------------------------------
	virtual void shutdown() override;

	//-----------------------------------------------------------
	// Updates data between frames
	// deltaTime (float): How much time has passed from last 
	//					  frame?
	//-----------------------------------------------------------
	virtual void update(float deltaTime);
	//-----------------------------------------------------------
	// Draw images on screen
	//-----------------------------------------------------------
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;		//Data for what is rendered
	aie::Font*			m_font;				//Holds font type
	SceneObject* sceneObject;				//Holds Scene data
	const float speed = 1000;				//holds a constant speed for all objects
	aie::Texture* tankTex;					//Holds texture for tank
	aie::Texture* ballTex;					//Holds texture for ball
	aie::Texture* barrelTex;				//Holds texture for barrel
	aie::Texture* emptyTex;					//Holds no texture, for objects that don't need textures
	bool shapeMode = true;					//Controls what tank spawns
};