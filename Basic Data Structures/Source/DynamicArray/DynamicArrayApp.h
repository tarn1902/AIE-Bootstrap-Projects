/*----------------------------------------
File Name: DynamicArrayApp.h
Purpose: Controls how the application behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "DynamicArray.h"
#include "Application.h"
#include "Renderer2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"
#include <stdio.h>

//-----------------------------------------------------------
// Object for controling the application
//-----------------------------------------------------------
class DynamicArrayApp : public aie::Application {
public:

	DynamicArrayApp();
	virtual ~DynamicArrayApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	DynamicArray<int>	array;
	int					highLight;
};