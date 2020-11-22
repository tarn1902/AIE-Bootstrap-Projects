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

class PhysicsEngineApp : public aie::Application {
public:

	PhysicsEngineApp();
	virtual ~PhysicsEngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void CreateScene1();
	void CreateScene2();
	void CreateScene3();
	void CreateScene4();

	void ResetScene();

protected:

	aie::Renderer2D* m_2dRenderer = nullptr;
	aie::Font* m_font = nullptr;
	PhysicsScene* physicsScene = nullptr;
	Sphere* rocket = nullptr;
	float* gravity = new float[2];
	float flightTime = 0;
	bool scene1 = true;
	bool scene2 = false;
	bool scene3 = false;
	bool scene4 = false;
	float mass1 = 4;
	float mass2 = 4;
	float force = 1;
};