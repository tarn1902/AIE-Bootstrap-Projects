/*----------------------------------------
File Name: SimulationObjects.h
Purpose: Runs all objects related systems
Author: Tarn Cooper
Modified: 07 June 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "glm/glm.hpp"
#include <vector>
#include "Renderer2D.h"

class SpriteBatch;

//Enum for refering to world object types
enum WorldObjectType
{
	SIMPLE_AI,
	WATER,
	FOOD,
	CAVE,
	PRED_AI,
};

using namespace std;

//Class for world objects
class WorldObject
{
public:
	vector<WorldObject*>* worldObjects;
	virtual void update(float delta) =0;
	virtual void draw(aie::Renderer2D* spriteBatch);
	float radius;
	glm::vec4 colour;
	glm::vec2 position;
	WorldObjectType type;
};

//Class for base resources which inherits from world object
class BaseResource:public WorldObject
{
	public:
	float amount;

	BaseResource(glm::vec2 position,glm::vec4 colour,float radius);
	void virtual update(float delta){};
};

//Class for Water which inherits from base resource
class Water:public BaseResource
{
	public:
	Water(glm::vec2 position);
};

//Class for food which inherits from base resource
class Food:public BaseResource
{
	public:
	Food(glm::vec2 position);
};

//Class for cave which inherits from base resource
class Cave:public BaseResource
{
	public:
	Cave(glm::vec2 position);
};

//Class for base agent which inherits from world object
class BaseAgent:public WorldObject
{
public:
	BaseAgent(glm::vec2 position, glm::vec4 colour, float radius);
	float findNearestResource(WorldObjectType type);
	glm::vec2 findResourceVector(WorldObjectType type);
	float tiredness;
	float food;
	float water;
};

//Class for Water which inherits from base agent
class Agent : public BaseAgent
{
public:
	float maxSpeed;
	virtual void update(float delta);
	virtual void draw(aie::Renderer2D* spriteBatch);
	void drawBar(aie::Renderer2D* spriteBatch, float value,int index);
	Agent(glm::vec2 position);
	float checkEatingDesirable();
	float checkSleepDesirable();
	float checkDrinkingDesirable();
	glm::vec2 gotoFood(float desirability,float delta);
	glm::vec2 gotoCave(float desirability,float delta);
	glm::vec2 gotoWater(float desirability,float delta);
};

//Class for AgentPred which inherits from base resource
class AgentPred : public BaseAgent
{
public:
	float maxSpeed;
	virtual void update(float delta);
	virtual void draw(aie::Renderer2D* spriteBatch);
	AgentPred(glm::vec2 position);
	float checkEatingDesirable();
	float checkSleepDesirable();
	float checkDrinkingDesirable();
	glm::vec2 gotoFood(float desirability, float delta);
	glm::vec2 gotoCave(float desirability, float delta);
	glm::vec2 gotoWater(float desirability, float delta);
};

//Class for world controller
class WorldController
{
public:
	vector<WorldObject*> worldObjects;
	void update(float delta);
	void draw(aie::Renderer2D* spriteBatch);
	void addObject(WorldObject* newObject);
};