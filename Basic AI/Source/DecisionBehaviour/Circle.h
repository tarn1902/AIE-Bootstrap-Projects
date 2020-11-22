/*----------------------------------------
File Name: Circle.h
Purpose: Class holding circle infomation
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include"Object.h"
class Circle : public Object
{
public:
//-----------------------------------------------------------
// Constructs Circle
//-----------------------------------------------------------
	Circle();
//-----------------------------------------------------------
// Destructs Box
//-----------------------------------------------------------
	~Circle();
	char shape = 'C';
	Vector2 Center;
	float radius;
};

