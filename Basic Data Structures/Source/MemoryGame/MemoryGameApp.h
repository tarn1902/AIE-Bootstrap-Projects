/*----------------------------------------
File Name: MemoryGameApp.cpp
Purpose: Controls how the application behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "DynamicArray.h"
#include "Card.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"
#include "Player.h"
#include "Button.h"
#include <iostream>
//-----------------------------------------------------------
// Object for controling the application
//-----------------------------------------------------------
class MemoryGameApp : public aie::Application {
public:

	MemoryGameApp();
	virtual ~MemoryGameApp();
	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();
	virtual void PlaceCards();
	virtual void PlaceUI();
	virtual void PlaceResults();
	virtual void PlaceMenu();
	virtual void ShuffleDeck();
	virtual void Reset();
	virtual void CreateDeck();

protected:
	//Renderer
	aie::Renderer2D*	m_2dRenderer;

	//Fonts
	aie::Font*			m_font;
	aie::Font*			titleFont;

	//intergers
	int delayReveal = 500;
	int delayResults = 250;
	int maxCardPairs = 18;
	int cardsRemain = 0;
	int cardHighlight = 0;
	int buttonHighlight = 0;
	int revealed1 = -1;
	int revealed2 = -1;

	//booleans
	bool playerTurn = true;
	bool inOptions = false;	
	bool gameStart = false;
	bool gamePause = true;
	bool textureError = false;

	//Arrays
	DynamicArray<Card*> deck;
	DynamicArray<Player*> players;
	DynamicArray<Button*> buttonGroup;
};