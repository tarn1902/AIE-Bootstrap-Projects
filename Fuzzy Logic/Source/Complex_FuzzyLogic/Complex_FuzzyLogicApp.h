/*----------------------------------------
File Name: Complex_FuzzyLogicApp.h
Purpose: Runs app
Author: Tarn Cooper
Modified: 07 June 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "FuzzyLogicEngine.h"

class WorldController;

//Class for Complex_FuzzyLogicApp
class Complex_FuzzyLogicApp : public aie::Application {
public:

	Complex_FuzzyLogicApp();
	virtual ~Complex_FuzzyLogicApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	
	static Fuzzy m_fuzzyEngine;  //not much of an engine but it's a start

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	WorldController* m_worldController;
};