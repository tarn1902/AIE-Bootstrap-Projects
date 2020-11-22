/*----------------------------------------
File Name: PhysicsEngineApp.h
Purpose: Runs application
Author: Tarn Cooper
Modified: 06 March 2020
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
#include <vector>
#include <Input.h>

class PhysicsEngineApp : public aie::Application {
public:

	PhysicsEngineApp();
	virtual ~PhysicsEngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float inDeltaTime);
	virtual void draw();


	void ChangeSelected(aie::Input* inInput, PhysicsObject* inObject, std::vector<PhysicsObject*> inActors);
	void SetRadiosToFalse();


protected:

	aie::Renderer2D* m_2dRenderer = nullptr;
	aie::Font* m_font = nullptr;


	PhysicsScene* physicsScene = nullptr;
	float* gravity = new float[2];
	float* startPos = new float[2];
	float* mass = new float;
	float* startVel = new float[2];
	float* radius = new float;
	float* colour = new float[4];
	float* extents = new float[2];
	int isObjectSize = 4;
	bool* isObject = new bool[isObjectSize];
	float* springCof = new float;
	float* damping = new float;
	float* restLength = new float;
	float selected = 0;
	float selectedAlt = 0;
	float* normal = new float[2];
	float* distance = new float;
	bool* isStatic = new bool;
	bool isPaused = false;

};