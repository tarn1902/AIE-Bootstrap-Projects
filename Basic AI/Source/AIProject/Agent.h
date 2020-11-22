/*----------------------------------------
File Name: Agent.h
Purpose: Class for AI behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Structs.h"
#include <list>
namespace aie
{
	class Renderer2D;
}

class Behaviour;

class Agent
{
public:
//-----------------------------------------------------------
// Constructs Agent
//-----------------------------------------------------------
	Agent();
//-----------------------------------------------------------
// Destructs Agent
//-----------------------------------------------------------
	virtual ~Agent();
//-----------------------------------------------------------
// Updates position of agent
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual void Update(float deltaTime);
//-----------------------------------------------------------
// Draw Agent at current position
// renderer (aie::Renderer2D*): How is it being drawn?
//-----------------------------------------------------------
	virtual void Draw(aie::Renderer2D* renderer);
	//-----------------------------------------------------------
	// Sets start node
	// node (Node*): Where is it's start node?
	//-----------------------------------------------------------
	void SetStartNode(Node* node);
//-----------------------------------------------------------
// Sets end node
// node (Node*): Where is it's end node?
//-----------------------------------------------------------
	void SetEndNode(Node* node);
//-----------------------------------------------------------
// Clears path
//-----------------------------------------------------------
	void ClearPath();
//-----------------------------------------------------------
// Uses Astar to find path to target Node
//-----------------------------------------------------------
	void AStar();
//-----------------------------------------------------------
// Used to predict best path to take
//-----------------------------------------------------------
	float Heuristics(Node* nextNode);
	
protected:
	std::vector<Node*> path;
	Node* startNode = nullptr;
	Node* endNode = nullptr;
	Colour colour;
	const int SIZE = 10;
	Vector2 m_Position;
};

