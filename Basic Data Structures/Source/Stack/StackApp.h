/*----------------------------------------
File Name: StackApp.h
Purpose: Controls how the application behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Stack.h"
#include "imgui.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

//-----------------------------------------------------------
// Object for controling the application
//-----------------------------------------------------------
class StackApp : public aie::Application {
public:

	StackApp();
	virtual ~StackApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	ListNode<int>*		highLight;
	Stack<int>			list;
};