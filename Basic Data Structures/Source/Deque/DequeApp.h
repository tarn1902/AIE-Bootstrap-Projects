/*----------------------------------------
File Name: DequeApp.h
Purpose: Controls how the application behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "LinkList.h"
#include "Deque.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"

//-----------------------------------------------------------
// Object for controling the application
//-----------------------------------------------------------
class DequeApp : public aie::Application {
public:

	DequeApp();
	virtual ~DequeApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	ListNode<int>*		highLight = nullptr;
	Deque<int>			list;
};