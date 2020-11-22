/*----------------------------------------
File Name: Button.cpp
Purpose: Holds each method for Button.h
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "Button.h"
#include "MemoryGameApp.h"

//-----------------------------------------------------------
// Contructs this object
//-----------------------------------------------------------
Button::Button()
{
	text = " ";
	font = nullptr;
}

//-----------------------------------------------------------
// Contructs this object
//	inText (const char*): What text will be displayed?
//	inFont (aie::Font*): What font will be used
//-----------------------------------------------------------
Button::Button(const char* inText, aie::Font* inFont)
{
	text = inText;
	font = inFont;
}

//-----------------------------------------------------------
// Destroys this object
//-----------------------------------------------------------
Button::~Button()
{
}

//-----------------------------------------------------------
// Draws button on screen
//	renderer (aie::Renderer2D*): What renderer will be used?
//	inXCord (float): What positon in X axis.
//	inYCord(float) : What positon in Y axis.
//	inWidth (float): What size in X axis.
//	inHeight (float) : What size in Y axis.
//	selected (bool): Is it currently selected in game?
//-----------------------------------------------------------
void Button::DrawButton(aie::Renderer2D* renderer, float inXCord, float inYCord, float inWidth, float inHeight, bool selected)
{
	if (selected)
	{
		renderer->setRenderColour(0, 1, 0, 1);
		renderer->drawBox(inXCord - 2, inYCord - 2, inWidth+20, inHeight+20);
		renderer->setRenderColour(1, 1, 1, 1);
		renderer->drawBox(inXCord, inYCord, inWidth, inHeight);
		renderer->setRenderColour(0, 0, 0, 1);
		renderer->drawText(font, text, inXCord - 75, inYCord -25);
	}
	else
	{
		renderer->setRenderColour(1, 1, 1, 1);
		renderer->drawBox(inXCord, inYCord, inWidth, inHeight);
		renderer->setRenderColour(0, 0, 0, 1);		
		renderer->drawText(font, text, inXCord -75, inYCord - 25);
	}
}
