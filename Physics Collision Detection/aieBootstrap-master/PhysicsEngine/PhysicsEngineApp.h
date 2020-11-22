/*----------------------------------------
File Name: PhysicsEngineApp.h
Purpose: Runs application
Author: Tarn Cooper
Modified: 10 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"
#include "Sphere.h"
#include "Box.h"
#include "Plane.h"

class PhysicsEngineApp : public aie::Application {
public:

	PhysicsEngineApp();
	virtual ~PhysicsEngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D* m_2dRenderer = nullptr;
	aie::Font* m_font = nullptr;
	PhysicsScene* physicsScene = nullptr;
	float* gravity = new float[2];

};