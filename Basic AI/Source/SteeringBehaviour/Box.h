/*----------------------------------------
File Name: Box.h
Purpose: Class holding box infomation
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Object.h"
class Box : public Object
{
public:
//-----------------------------------------------------------
// Constructs Box
//-----------------------------------------------------------
	Box();
//-----------------------------------------------------------
// Destructs Box
//-----------------------------------------------------------
	~Box();
	char shape = 'B';
	Vector2 minPos;
	Vector2 maxPos;
	float lengthX;
	float lengthY;
	float maxRadius;
};

