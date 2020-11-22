/*----------------------------------------
File Name: Grid.cpp
Purpose: function for Grid
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "Grid.h"
#include "Input.h"
#include "Renderer2D.h"
#include <iostream>

//Constructs clean grid
Grid::Grid()
{
	CreateNodes();
	CreateEdges();
}

//Destructs grid
Grid::~Grid()
{
	for each (Node* node in gridNodes)
	{
		delete node;
	}
}

//Function to create basic node
void Grid::CreateNodes()
{
	for (int i = GRID_SPACING; i < SCREEN_WIDTH; i += GRID_SPACING)
	{
		for (int j = GRID_SPACING; j < SCREEN_HEIGHT; j += GRID_SPACING)
		{
			Node* node = new Node();
			node->position = Vector2((float)i, (float)j);
			gridNodes.push_back(node);
		}
	}
}

//Function to create all possible edges
void Grid::CreateEdges()
{
	for (int i = 0; i < gridNodes.size(); ++i)
	{
		//Creates edges for right
		if (gridNodes.at(i)->position.x - GRID_SPACING > 0)
		{
			Edge* edge = new Edge();
			edge->target = gridNodes.at(i - NEXT_HORIZONTAL_INDEX);
			edge->cost++;
			gridNodes.at(i)->connections.push_back(edge);
		}
		//Creates edges for left
		if (gridNodes.at(i)->position.x + GRID_SPACING < SCREEN_WIDTH)
		{
			Edge* edge = new Edge();
			edge->target = gridNodes.at(i + NEXT_HORIZONTAL_INDEX);
			edge->cost++;
			gridNodes.at(i)->connections.push_back(edge);
		}
		//Creates edges for bottom
		if (gridNodes.at(i)->position.y - GRID_SPACING > 0)
		{
			Edge* edge = new Edge();
			edge->target = gridNodes.at(i - NEXT_VERTICAL_INDEX);
			edge->cost++;
			gridNodes.at(i)->connections.push_back(edge);
		}
		//Creates edges for top
		if (gridNodes.at(i)->position.y + GRID_SPACING < SCREEN_HEIGHT)
		{
			Edge* edge = new Edge();
			edge->target = gridNodes.at(i + NEXT_VERTICAL_INDEX);
			edge->cost++;
			gridNodes.at(i)->connections.push_back(edge);
		}
	}
}

//Removes all endges from node
void Grid::RemoveNodeEdges(Node* node)
{
	for each (Edge* edge in node->connections)
	{
		for each (Edge* targetEdge in edge->target->connections)
		{
			if (targetEdge->target == node)
			{
				auto iter = std::find(edge->target->connections.begin(), edge->target->connections.end(), targetEdge);
				edge->target->connections.erase(iter);
				break;
			}
		}
	}
	node->connections.clear();
	node->colour.blue = 1;
	node->colour.red = 0;
	node->colour.green = 0;
}

//Usable node in wall
void Grid::CreateDoor(Node* node)
{
	node->connections.push_back(new Edge());
	for (int i = 0; i < gridNodes.size(); ++i)
	{
		if (gridNodes.at(i)->connections.size() == 0)
		{
			continue;
		}
		gridNodes.at(i)->connections.clear();
		//Creates edges for right
		if (gridNodes.at(i)->position.x - GRID_SPACING > 0)
		{
			if (gridNodes.at(i - NEXT_HORIZONTAL_INDEX)->connections.size() != 0)
			{
				Edge* edge = new Edge();
				edge->target = gridNodes.at(i - NEXT_HORIZONTAL_INDEX);
				edge->cost++;
				gridNodes.at(i)->connections.push_back(edge);
			}		
		}
		//Creates edges for left
		if (gridNodes.at(i)->position.x + GRID_SPACING < SCREEN_WIDTH)
		{
			if (gridNodes.at(i + NEXT_HORIZONTAL_INDEX)->connections.size() != 0)
			{
				Edge* edge = new Edge();
				edge->target = gridNodes.at(i + NEXT_HORIZONTAL_INDEX);
				edge->cost++;
				gridNodes.at(i)->connections.push_back(edge);
			}
		}
		//Creates edges for bottom
		if (gridNodes.at(i)->position.y - GRID_SPACING > 0)
		{
			if (gridNodes.at(i - NEXT_VERTICAL_INDEX)->connections.size() != 0)
			{
				Edge* edge = new Edge();
				edge->target = gridNodes.at(i - NEXT_VERTICAL_INDEX);
				edge->cost++;
				gridNodes.at(i)->connections.push_back(edge);
			}
		}
		//Creates edges for top
		if (gridNodes.at(i)->position.y + GRID_SPACING < SCREEN_HEIGHT)
		{
			if (gridNodes.at(i + NEXT_VERTICAL_INDEX)->connections.size() != 0)
			{
				Edge* edge = new Edge();
				edge->target = gridNodes.at(i + NEXT_VERTICAL_INDEX);
				edge->cost++;
				gridNodes.at(i)->connections.push_back(edge);
			}
		}
	}
	//sets colour of wall
	node->colour.blue = 1;
	node->colour.red = 1;
	node->colour.green = 1;
}

//Creates wall of unusable nodes from one point to other
void Grid::CreateWall(int startIndex, int indexDistance, int directionIndex)
{
	for (int i = startIndex; i <= startIndex + indexDistance; i += directionIndex)
	{
		RemoveNodeEdges(gridNodes[i]);
	}
}

//removes a single usable node
void Grid::CreateBlock(Node* node)
{
	RemoveNodeEdges(node);
}

//Checks if node mouse is hovering over node
Node* Grid::HighlightNode(Node* node, aie::Input* input, Node* selectedNode)
{
	if (node->connections.size() != 0)
	{
		if (node->position.x + GRID_SPACING / 2 > input->getMouseX() && node->position.x - GRID_SPACING / 2 < input->getMouseX() && node->position.y + GRID_SPACING / 2 > input->getMouseY() && node->position.y - GRID_SPACING / 2 < input->getMouseY())
		{
			return node;
		}
	}
	return selectedNode;
}

//gets node using index
Node* Grid::GetNode(int index)
{
	return gridNodes[index];
}

//Gets grid list
std::vector<Node*> Grid::GetGrid()
{
	return gridNodes;
}

//creates preconstruct level
void Grid::CreateLevel()
{
	//Creates Vertical Wall
	CreateWall(0 + NEXT_HORIZONTAL_INDEX * HALF_WIDTH_INDEX, NEXT_VERTICAL_INDEX * MAX_HEIGHT_INDEX, NEXT_VERTICAL_INDEX);
	CreateWall(0 + NEXT_HORIZONTAL_INDEX * MAX_WIDTH_INDEX, NEXT_VERTICAL_INDEX * MAX_HEIGHT_INDEX, NEXT_VERTICAL_INDEX);
	CreateWall(0, NEXT_VERTICAL_INDEX * MAX_HEIGHT_INDEX, NEXT_VERTICAL_INDEX);

	//Creates Horizontal Wall
	CreateWall(0 + NEXT_VERTICAL_INDEX * HALF_HEIGHT_INDEX, NEXT_HORIZONTAL_INDEX * MAX_WIDTH_INDEX, NEXT_HORIZONTAL_INDEX);
	CreateWall(0 + NEXT_VERTICAL_INDEX * MAX_HEIGHT_INDEX, NEXT_HORIZONTAL_INDEX * MAX_WIDTH_INDEX, NEXT_HORIZONTAL_INDEX);
	CreateWall(0, NEXT_HORIZONTAL_INDEX * MAX_WIDTH_INDEX, NEXT_HORIZONTAL_INDEX);

	//Create Doors on Vertical wall
	CreateDoor(gridNodes[0 + NEXT_HORIZONTAL_INDEX * HALF_WIDTH_INDEX + NEXT_VERTICAL_INDEX * 9]);
	CreateDoor(gridNodes[0 + NEXT_HORIZONTAL_INDEX * HALF_WIDTH_INDEX + NEXT_VERTICAL_INDEX * 25]);

	//Create Doors on horizontal wall
	CreateDoor(gridNodes[0 + NEXT_VERTICAL_INDEX * HALF_HEIGHT_INDEX + NEXT_HORIZONTAL_INDEX * 25]);
	CreateDoor(gridNodes[0 + NEXT_VERTICAL_INDEX * HALF_HEIGHT_INDEX + NEXT_HORIZONTAL_INDEX * 37]);

}

//Draws grid on renderer
void Grid::drawGrid(aie::Renderer2D* renderer)
{
	for each (Node* node in gridNodes)
	{
		renderer->setRenderColour(node->colour.red, node->colour.green, node->colour.blue);
		renderer->drawBox(node->position.x, node->position.y, (float)GRID_BLOCK, (float)GRID_BLOCK);

	}
}