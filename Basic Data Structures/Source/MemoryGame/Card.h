/*----------------------------------------
File Name: Card.cpp
Purpose: Controls how cards are displayed
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once

//-----------------------------------------------------------
// namespace for external classes
//-----------------------------------------------------------
namespace aie
{
	class Texture;
	class Renderer2D;
}

//-----------------------------------------------------------
// Object for displaying a card
//-----------------------------------------------------------
class Card
{
public:
	Card();
	Card(aie::Texture*);
	~Card();
	void DrawCard(aie::Renderer2D*, float, float, float, float, bool, bool, bool);
	void SetOut(bool);
	bool GetOut();
	aie::Texture* picture = nullptr;
private:
	bool out = false;

};

