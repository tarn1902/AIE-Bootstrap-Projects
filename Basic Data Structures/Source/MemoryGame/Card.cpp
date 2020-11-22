/*----------------------------------------
File Name: Card.cpp
Purpose: Holds each method for Card.h
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "Card.h"
#include "Renderer2D.h"

//-----------------------------------------------------------
// Contructs this object
//-----------------------------------------------------------
Card::Card()
{
	picture = nullptr;
	out = false;
}

//-----------------------------------------------------------
// Contructs this object
//	inPicture (aie::Texture*): What picture will be displayed?
//-----------------------------------------------------------
Card::Card(aie::Texture* inPicture)
{
	picture = inPicture;
	out = false;
}

//-----------------------------------------------------------
// Destroys this object
//-----------------------------------------------------------
Card::~Card()
{

}

//-----------------------------------------------------------
// Draws card on screen
//	renderer (aie::Renderer2D*): What renderer will be used?
//	inXCord (float): What positon in X axis.
//	inYCord(float) : What positon in Y axis.
//	inWidth (float): What size in X axis.
//	inHeight (float) : What size in Y axis.
//	selected (bool): Is it currently selected in game?
//	revealeded (bool): Is it being revealeded?
//	playerTurn (bool): Which players Turn?
//-----------------------------------------------------------
void Card::DrawCard(aie::Renderer2D* renderer, float inXCord, float inYCord, float inWidth, float inHeight, bool selected, bool revealeded, bool playerTurn)
{
	if (selected)
	{
		if (playerTurn)
		{
			renderer->setRenderColour(1, 0, 0, 1);
			renderer->drawBox(inXCord - 2, inYCord - 2, inWidth + 20, inHeight + 20);
		}
		else
		{
			renderer->setRenderColour(0, 0, 1, 1);
			renderer->drawBox(inXCord - 2, inYCord - 2, inWidth + 20, inHeight + 20);
		}
	}
	if (revealeded)
	{
		renderer->setUVRect(0, 0, 1, 1);
		renderer->setRenderColour(1, 1, 1, 1);
		renderer->drawBox(inXCord, inYCord, inWidth, inHeight);
		renderer->drawSprite(picture, inXCord, inYCord, inWidth, inHeight);
	}
	else if (out)
	{
		renderer->setUVRect(0, 0, 1, 1);
		renderer->setRenderColour(0, 1, 0, 1);
		renderer->drawBox(inXCord, inYCord, inWidth, inHeight);
		renderer->drawSprite(picture, inXCord, inYCord, inWidth, inHeight);
	}
	else
	{
		renderer->setRenderColour(1, 1, 1, 1);
		renderer->drawBox(inXCord, inYCord, inWidth, inHeight);
	}
}

//-----------------------------------------------------------
// Sets the out boolean
//	inOut (boolean): What is out set to?
//-----------------------------------------------------------
void Card::SetOut(bool inOut)
{
	out = inOut;
}

//-----------------------------------------------------------
// Gets the out boolean
//	return (boolean): returns out
//-----------------------------------------------------------
bool Card::GetOut()
{
	return out;
}
