/*----------------------------------------
File Name: Agent.cpp
Purpose: Functions for agent
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "Agent.h"
#include "Renderer2D.h"
#include <iostream>
#include <assert.h>
#include <algorithm>

//Changes agent to red
Agent::Agent()
{
	colour.blue = 0;
	colour.green = 0;
}

//Does nothing
Agent::~Agent()
{
}

//Goes through each Node in list from start till reaches endNode
void Agent::Update(float deltaTime)
{
	if (path.size() >= 2)
	{
		startNode = path.at(1);
		m_Position = startNode->position;
		path.erase(path.begin(), path.begin() + 1);
	}

	if (path.size() == 1)
	{
		path.clear();
		endNode = nullptr;
	}
};

//Sets colour and draws box at location
void Agent::Draw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(colour.red, colour.green, colour.blue, colour.alpha);
	renderer->drawBox(m_Position.x, m_Position.y, (float)SIZE, (float)SIZE);
};


//Sets startnode and position
void Agent::SetStartNode(Node* node)
{
	startNode = node;
	m_Position = node->position;
}

//Sets endNode
void Agent::SetEndNode(Node* node)
{
	endNode = node;
}

//Clears path list
void Agent::ClearPath()
{
	path.clear();
}

//Uses A* algorthim to find shortest path to destination
void Agent::AStar()
{
	// Validate the input
	path = std::vector<Node*>();

	if (startNode == nullptr || endNode == nullptr)
	{
		assert(startNode == nullptr || endNode == nullptr);
	}

	if (startNode == endNode)
	{
		return;
	}

	startNode->gScore = 0;
	startNode->parent = nullptr;

	std::vector<Node*> openList = std::vector<Node*>();
	std::vector<Node*> closedList = std::vector<Node*>();
	Node* currentNode = nullptr;

	openList.push_back(startNode);

	while (!openList.empty())
	{

		std::sort(openList.begin(), openList.end(), [](const Node* lhs, const Node* rhs) { return lhs->fScore < rhs->fScore; });

		currentNode = openList[0];
		if (currentNode == endNode)
		{
			break;
		}

		openList.erase(openList.begin());
		closedList.push_back(currentNode);

		for (int i = 0; i < currentNode->connections.size(); i++)
		{
			Edge* edge = currentNode->connections[i];
			if (std::find(closedList.begin(), closedList.end(), edge->target) == closedList.end())
			{

				float gScore = currentNode->gScore + edge->cost;
				float hScore = Heuristics(edge->target);
				float fScore = gScore + hScore;
				if (std::find(openList.begin(), openList.end(), edge->target) == openList.end())
				{
					edge->target->gScore = gScore;
					edge->target->fScore = fScore;
					edge->target->parent = currentNode;
					openList.push_back(edge->target);
				}
				else if (gScore < edge->target->gScore)
				{
					edge->target->gScore = gScore;
					edge->target->fScore = fScore;
					edge->target->parent = currentNode;
				}
			}
		}
	}
	currentNode = endNode;

	while (currentNode != nullptr)
	{
		path.insert(path.begin(), currentNode);
		currentNode = currentNode->parent;
	}
	return;
}


// uses Manhattan distance to support A* algorthim in finding shortest path
float Agent::Heuristics(Node* nextNode)
{
	return abs(nextNode->position.x - endNode->position.x) + abs(nextNode->position.y - endNode->position.y);
}
