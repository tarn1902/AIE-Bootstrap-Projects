/*----------------------------------------
File Name: AIProjectApp.h
Purpose: Bunch of structs
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <vector>
#include "../MathsLibrarySLL/MathsLibrarySLL.h"

typedef Vec2<float> Vector2;
struct Node;

struct Edge
{
public:
	Node* target = nullptr;
	float cost = 0;
	
};

struct Colour
{
	float red = 1;
	float green = 1;
	float blue = 1;
	float alpha = 1;
};

struct Node
{
public:
	Vector2 position = Vector2();
	float gScore = 0;
	float fScore = 0;
	Node* parent = nullptr;
	std::vector< Edge* > connections;
	Colour colour;
};

struct Circle
{
	Vector2 Center;
	float radius;
};