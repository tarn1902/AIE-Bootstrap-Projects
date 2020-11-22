/*----------------------------------------
File Name: Stack.h
Purpose: Controls how the button is displayed
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <string>

//-----------------------------------------------------------
// namespace for external classes
//-----------------------------------------------------------
namespace aie
{
	class Font;
	class Renderer2D;
}

//-----------------------------------------------------------
// Object for displaying a button
//-----------------------------------------------------------
class Button
{
public:
	Button();
	Button(const char*, aie::Font*);
	~Button();
	void DrawButton(aie::Renderer2D*, float, float, float, float, bool);
	const char* text = "";
	aie::Font* font = nullptr;
};

