/*----------------------------------------
File Name: HashingApp.h
Purpose: Controls how the application behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "HashTable.h"
#include <string>
#include "Texture.h"
#include "Font.h"
#include "Input.h"

//-----------------------------------------------------------
// Object for controling the application
//-----------------------------------------------------------
class HashingApp : public aie::Application {
public:

	HashingApp();
	virtual ~HashingApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	HashTable<const char*, aie::Texture*> hashTable = HashTable<const char*, aie::Texture*>(100);
	int selection = 0;
	const char* list[4];
};