/*----------------------------------------
File Name: AIProjectApp.h
Purpose: Class for Grid
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Structs.h"
namespace aie
{
	class Input;
	class Renderer2D;
}

class Player;

class Grid
{
public:
//-----------------------------------------------------------
// Constructs Grid
//-----------------------------------------------------------
	Grid();
//-----------------------------------------------------------
// Destructs Agent
//-----------------------------------------------------------
	~Grid();
//-----------------------------------------------------------
// Creates a line of empty nodes
// startIndex (int): Where does wall start?
// endIndex (int): Where does it end?
// directionIndex (int): In which direction?
//-----------------------------------------------------------
	void CreateWall(int startIndex, int endIndex, int directionIndex);
//-----------------------------------------------------------
// Opening in wall
// node (Node*): Which node?
//-----------------------------------------------------------
	void CreateDoor(Node* node);
//-----------------------------------------------------------
// Closes openings
// node (Node*): Which node?
//-----------------------------------------------------------
	void CreateBlock (Node* node);
//-----------------------------------------------------------
// Creates level
//-----------------------------------------------------------
	void CreateLevel();
//-----------------------------------------------------------
// Get Node from index
// index (int): What index?
// return (Node*): returns node pointer
//-----------------------------------------------------------
	Node* GetNode(int index);
//-----------------------------------------------------------
// Checks if node is usable
// node (Node*): What node to check?
// input (aie::Input*): How to check mouse location?
// selectedNode (Node*): If fails?
//	return (Node*): returns node ok to use
//-----------------------------------------------------------
	Node* HighlightNode(Node* node, aie::Input* input, Node* selectedNode);
//-----------------------------------------------------------
// Gets grid list
// return (std::vector<Node*>): return grid list
//-----------------------------------------------------------
	std::vector<Node*> GetGrid();
//-----------------------------------------------------------
// Draws grid
// renderer (aie::Renderer2D*): how to draw it?
//-----------------------------------------------------------
	void drawGrid(aie::Renderer2D* renderer);
	
protected:
//-----------------------------------------------------------
// Creates Node
//-----------------------------------------------------------
	void CreateNodes();
//-----------------------------------------------------------
// Creates Edge
//-----------------------------------------------------------
	void CreateEdges();
	void RemoveNodeEdges(Node* node);
	
	const int GRID_SPACING = 20;
	const int SCREEN_HEIGHT = 720;
	const int SCREEN_WIDTH = 1280;
	const int NEXT_HORIZONTAL_INDEX = (SCREEN_HEIGHT - GRID_SPACING) / GRID_SPACING;
	const int NEXT_VERTICAL_INDEX = 1;
	const int MAX_HEIGHT_INDEX = (SCREEN_HEIGHT / GRID_SPACING) - 2;
	const int MAX_WIDTH_INDEX = (SCREEN_WIDTH / GRID_SPACING) - 2;
	const int HALF_HEIGHT_INDEX = MAX_HEIGHT_INDEX / 2;
	const int HALF_WIDTH_INDEX = MAX_WIDTH_INDEX / 2;
	const int GRID_BLOCK = 10;

	std::vector<Node*> gridNodes;
};



