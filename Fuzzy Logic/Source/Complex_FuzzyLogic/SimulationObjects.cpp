/*----------------------------------------
File Name: SimulationObjects.cpp
Purpose: Runs function for simulating 
objects.
Author: Tarn Cooper
Modified: 07 June 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "SimulationObjects.h"
#include "FuzzyLogicEngine.h"
#include "Complex_FuzzyLogicApp.h"
#include "Texture.h"
#include <iostream>

//-----------------------------------------------------------
// Draws sprite to screen
// spriteBatch (aie::Render2D*): What renderer will be used?
//-----------------------------------------------------------
void WorldObject::draw(aie::Renderer2D* spriteBatch)
{
	int segments = 20;

	spriteBatch->setRenderColour(colour.r, colour.g, colour.b, colour.a);
	spriteBatch->drawSprite(nullptr, position.x, position.y, radius, radius);
}

//-----------------------------------------------------------
// Constructs base agent
// position (glm::vec2): What is the positon of agent?
// position (glm::vec2): What is the positon of agent?
// colour (glm::vec4): What is the colour of agent?
// colour (float): What is the radius of agent?
//-----------------------------------------------------------
BaseAgent::BaseAgent(glm::vec2 position, glm::vec4 colour, float radius)
{
	this->position = position;
	this->colour = colour;
	this->radius = radius;
}

//-----------------------------------------------------------
// Constructs base resorce
// position (glm::vec2): What is the positon of agent?
// position (glm::vec2): What is the positon of agent?
// colour (glm::vec4): What is the colour of agent?
// colour (float): What is the radius of agent?
//-----------------------------------------------------------
BaseResource::BaseResource(glm::vec2 position,glm::vec4 colour,float radius)
{
	this->position = position;
	this->colour = colour;
	this->radius = radius;
}

//-----------------------------------------------------------
// Constructs Water
// position (glm::vec2): What is the positon of agent?
//-----------------------------------------------------------
Water::Water(glm::vec2 position):BaseResource(position,glm::vec4(0,0,1,1),20)
{
	type = WATER;
}

//-----------------------------------------------------------
// Constructs Food
// position (glm::vec2): What is the positon of agent?
//-----------------------------------------------------------
Food::Food(glm::vec2 position):BaseResource(position,glm::vec4(0,1,0,1),20)
{
	type = FOOD;
}

//-----------------------------------------------------------
// Constructs Cave
// position (glm::vec2): What is the positon of agent?
//-----------------------------------------------------------
Cave::Cave(glm::vec2 position):BaseResource(position,glm::vec4(1,1,1,1),20)
{
	type = CAVE;
}

//-----------------------------------------------------------
// Constructs agent
// position (glm::vec2): What is the positon of agent?
//-----------------------------------------------------------
Agent::Agent(glm::vec2 position) : BaseAgent(position, glm::vec4(1, 1, 0, 1), 20)
{
	tiredness = 1;
	food = 1;
	water = 1;
	type = SIMPLE_AI;
	maxSpeed = 150;
};

//-----------------------------------------------------------
// Constructs AgentPred
// position (glm::vec2): What is the positon of agent?
//-----------------------------------------------------------
AgentPred::AgentPred(glm::vec2 position) : BaseAgent(position, glm::vec4(1, 0, 1, 1), 20)
{
	tiredness = 1;
	food = 1;
	water = 1;
	type = PRED_AI;
	maxSpeed = 150;
};

//-----------------------------------------------------------
// Draws bar to screen
// spriteBatch (aie::Renderer2D*): What is the renderer used?
// value (float): What is the value in bar?
// index (int): What is the section and index of bar?
//-----------------------------------------------------------
void Agent::drawBar(aie::Renderer2D* spriteBatch, float value, int index)
{
	glm::vec4 colours[] = {glm::vec4(1,0,0,1),glm::vec4(0,1,0,1),glm::vec4(0,0,1,1)};
	glm::vec2 leftPos(10,700);
	float barLength = 90;
	float barHeight = 10;
	glm::vec4 white(1,1,1,1);
	glm::vec4 back(1, 1, 1, .25f);
	glm::vec4 colour(.3,.3,.3,1);
	glm::vec2 extents(barLength,barHeight);
	glm::vec2 centrePos = leftPos;

	centrePos.y -= barHeight * 3 * index;
	centrePos.x += barLength;
	

	float colorBarLength = barLength * value;
	glm::vec2 colorExtents = glm::vec2(colorBarLength,barHeight);
	glm::vec2 colorCentrePos = leftPos;
	colorCentrePos.y -= barHeight * 3 * index;
	colorCentrePos.x += colorBarLength;
	colour = colours[index];
	
	spriteBatch->setRenderColour(colour.r, colour.g, colour.b, colour.a);
	spriteBatch->drawSprite(nullptr, colorCentrePos.x - colorExtents.x / 2, colorCentrePos.y - colorExtents.y / 2, colorExtents.x, colorExtents.y);

	spriteBatch->setRenderColour(back.r, back.g, back.b, back.a);
	spriteBatch->drawSprite(nullptr, centrePos.x - extents.x / 2, centrePos.y - extents.y / 2, extents.x, extents.y);
}

//-----------------------------------------------------------
// Calculates distance of nearest resouce of specfic type
// type (WorldObjectType): What type of resouce is it?
//-----------------------------------------------------------
float BaseAgent::findNearestResource(WorldObjectType type)
{
	float minDistance = 1000000;
	for(auto object:*worldObjects)
	{
		if(object->type == type)
		{
			float distance = glm::length(object->position - position);
			if(distance < minDistance)
			{
				minDistance = distance;
			}
		}
	}
	return minDistance;
}

//-----------------------------------------------------------
// Calculates direction of nearest resouce of specfic type
// type (WorldObjectType): What type of resouce is it?
//-----------------------------------------------------------
glm::vec2 BaseAgent::findResourceVector(WorldObjectType type)
{
	float minDistance = 1000000;
	glm::vec2 target;
	for(auto object:*worldObjects)
	{
		if(object->type == type)
		{
			float distance = glm::length(object->position - position);
			if(distance < minDistance)
			{
				minDistance = distance;
				target = object->position;
			}
		}
	}
	glm::vec2 vector;
	if(minDistance<1)
	{
		vector = glm::vec2(0,0);
	}
	else
	{
		vector = (target - position)/minDistance;
	}
	return vector;
}

//-----------------------------------------------------------
// Draws agent to screen
// spriteBatch (aie::Renderer2D*): What is the renderer used?
//-----------------------------------------------------------
void Agent::draw(aie::Renderer2D* spriteBatch)
{
	BaseAgent::draw(spriteBatch);

	//For Testing
	//drawBar(spriteBatch, tiredness,0);
	//drawBar(spriteBatch, food,1);
	//drawBar(spriteBatch, water,2);
}

//-----------------------------------------------------------
// Draws agent to screen
// spriteBatch (aie::Renderer2D*): What is the renderer used?
//-----------------------------------------------------------
void AgentPred::draw(aie::Renderer2D* spriteBatch)
{
	BaseAgent::draw(spriteBatch);
}

//-----------------------------------------------------------
// Checks how desireable eating is
// return (float): Returns desirablity
//-----------------------------------------------------------
float Agent::checkEatingDesirable()
{
	float desire = 0; //this is the return value which will be how much
	//our AI desires food
	float foodRange = findNearestResource(FOOD);
	//how far is the nearest food source
	//how hungry are we...
	float hungry = Complex_FuzzyLogicApp::m_fuzzyEngine.hungry->getMembership(food);
	//how full are we...
	float full = Complex_FuzzyLogicApp::m_fuzzyEngine.full->getMembership(food);
	//are we very hungry?
	float veryHungry  = Complex_FuzzyLogicApp::m_fuzzyEngine.veryHungry->getMembership(food);
	//how close are we to food...
	float foodRangeClose = Complex_FuzzyLogicApp::m_fuzzyEngine.veryNear->getMembership(foodRange);
	float foodRangeMedium = Complex_FuzzyLogicApp::m_fuzzyEngine.mediumRange->getMembership(foodRange);
	float foodRangeFar = Complex_FuzzyLogicApp::m_fuzzyEngine.farAway->getMembership(foodRange);
	//is this a very desirable action?
	float veryDesirableValue = Fuzzy::OR(Fuzzy::AND(foodRangeClose,hungry),veryHungry);
	//is it a desirable action?
	float desirableValue = Fuzzy::AND(Fuzzy::NOT(foodRangeClose),hungry);
	//is in undesirable?  In this case if we are full it's undesirable
	float undesirableValue = full;
	//set up our maximum values ready to defuzzify
	float maxVeryDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.veryDesirable->getMaxMembership();
	float maxDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.desirable->getMaxMembership();
	float maxUndesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.undesirable->getMaxMembership();
	//defuzzify
	desire = maxVeryDesirable*veryDesirableValue + maxDesirable* desirableValue + maxUndesirable*undesirableValue;
	desire /= (.1f + veryDesirableValue + desirableValue + undesirableValue);
	//return our final desire
	cout << desire << endl;
	return desire;
}

//-----------------------------------------------------------
// Checks how desireable eating is
// return (float): Returns desirablity
//-----------------------------------------------------------
float AgentPred::checkEatingDesirable()
{
	float desire = 0; //this is the return value which will be how much
	//our AI desires food
	float foodRange = findNearestResource(SIMPLE_AI);
	float predRange = findNearestResource(PRED_AI);
	//how far is the nearest food source
	//how hungry are we...
	float hungry = Complex_FuzzyLogicApp::m_fuzzyEngine.hungry->getMembership(food);
	//how full are we...
	float full = Complex_FuzzyLogicApp::m_fuzzyEngine.full->getMembership(food);
	//are we very hungry?
	float veryHungry = Complex_FuzzyLogicApp::m_fuzzyEngine.veryHungry->getMembership(food);
	//how close are we to food...
	float foodRangeClose = Complex_FuzzyLogicApp::m_fuzzyEngine.veryNear->getMembership(foodRange);
	float foodRangeMedium = Complex_FuzzyLogicApp::m_fuzzyEngine.mediumRange->getMembership(foodRange);
	float foodRangeFar = Complex_FuzzyLogicApp::m_fuzzyEngine.farAway->getMembership(foodRange);
	//is this a very desirable action?
	float veryDesirableValue = Fuzzy::OR(Fuzzy::AND(foodRangeClose, hungry), veryHungry);
	//is it a desirable action?
	float desirableValue = Fuzzy::AND(Fuzzy::NOT(foodRangeClose), hungry);
	//is in undesirable?  In this case if we are full it's undesirable
	float undesirableValue = Fuzzy::OR(full, predRange);
	//set up our maximum values ready to defuzzify
	float maxVeryDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.veryDesirable->getMaxMembership();
	float maxDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.desirable->getMaxMembership();
	float maxUndesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.undesirable->getMaxMembership();
	//defuzzify
	desire = maxVeryDesirable * veryDesirableValue + maxDesirable * desirableValue + maxUndesirable * undesirableValue;
	desire /= (.1f + veryDesirableValue + desirableValue + undesirableValue);
	//return our final desire
	cout << desire << endl;
	return desire;
}

//-----------------------------------------------------------
// Checks how desireable sleeping is
// return (float): Returns desirablity
//-----------------------------------------------------------
float Agent::checkSleepDesirable()
{
	float desire = 0; //this is the return value which will be how much
	//our AI desires food
	float caveRange = findNearestResource(CAVE);
	//how far is the nearest food source
	//how hungry are we...
	float tired = Complex_FuzzyLogicApp::m_fuzzyEngine.tired->getMembership(tiredness);
	//how full are we...
	float active = Complex_FuzzyLogicApp::m_fuzzyEngine.superActive->getMembership(tiredness);
	//are we very hungry?
	float awake  = Complex_FuzzyLogicApp::m_fuzzyEngine.awake->getMembership(tiredness);
	//how close are we to food...
	float caveClose = Complex_FuzzyLogicApp::m_fuzzyEngine.veryNear->getMembership(caveRange);
	float caveMedium = Complex_FuzzyLogicApp::m_fuzzyEngine.mediumRange->getMembership(caveRange);
	float caveFar = Complex_FuzzyLogicApp::m_fuzzyEngine.farAway->getMembership(caveRange);
	//is this a very desirable action?
	float veryDesirableValue = Fuzzy::OR(Fuzzy::AND(caveClose,awake),tired);
	//is it a desirable action?
	float desirableValue = Fuzzy::AND(Fuzzy::NOT(caveClose),awake);
	//is in undesirable?  In this case if we are full it's undesirable
	float undesirableValue = active;
	//set up our maximum values readt to defuzzify
	float maxVeryDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.veryDesirable->getMaxMembership();
	float maxDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.desirable->getMaxMembership();
	float maxUndesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.undesirable->getMaxMembership();
	//defuzzify
	desire = maxVeryDesirable*veryDesirableValue + maxDesirable* desirableValue + maxUndesirable*undesirableValue;
	desire /= (.1f + veryDesirableValue + desirableValue + undesirableValue);
	//return our final desire
	cout << desire << endl;
	return desire;
}

//-----------------------------------------------------------
// Checks how desireable sleeping is
// return (float): Returns desirablity
//-----------------------------------------------------------
float  AgentPred::checkSleepDesirable()
{
	float desire = 0; //this is the return value which will be how much
	//our AI desires food
	float caveRange = findNearestResource(CAVE);
	float predRange = findNearestResource(PRED_AI);
	//how far is the nearest food source
	//how hungry are we...
	float tired = Complex_FuzzyLogicApp::m_fuzzyEngine.tired->getMembership(tiredness);
	//how full are we...
	float active = Complex_FuzzyLogicApp::m_fuzzyEngine.superActive->getMembership(tiredness);
	//are we very hungry?
	float awake = Complex_FuzzyLogicApp::m_fuzzyEngine.awake->getMembership(tiredness);
	//how close are we to food...
	float caveClose = Complex_FuzzyLogicApp::m_fuzzyEngine.veryNear->getMembership(caveRange);
	float caveMedium = Complex_FuzzyLogicApp::m_fuzzyEngine.mediumRange->getMembership(caveRange);
	float caveFar = Complex_FuzzyLogicApp::m_fuzzyEngine.farAway->getMembership(caveRange);
	//is this a very desirable action?
	float veryDesirableValue = Fuzzy::OR(Fuzzy::AND(caveClose, awake), tired);
	//is it a desirable action?
	float desirableValue = Fuzzy::AND(Fuzzy::NOT(caveClose), awake);
	//is in undesirable?  In this case if we are full it's undesirable
	float undesirableValue = Fuzzy::OR(active, predRange);
	//set up our maximum values readt to defuzzify
	float maxVeryDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.veryDesirable->getMaxMembership();
	float maxDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.desirable->getMaxMembership();
	float maxUndesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.undesirable->getMaxMembership();
	//defuzzify
	desire = maxVeryDesirable * veryDesirableValue + maxDesirable * desirableValue + maxUndesirable * undesirableValue;
	desire /= (.1f + veryDesirableValue + desirableValue + undesirableValue);
	//return our final desire
	cout << desire << endl;
	return desire;
}

//-----------------------------------------------------------
// Checks how desireable drinking is
// return (float): Returns desirablity
//-----------------------------------------------------------
float Agent::checkDrinkingDesirable()
{
	float desire = 0; //this is the return value which will be how much
	//our AI desires food
	float waterRange = findNearestResource(WATER);
	//how far is the nearest food source
	//how hungry are we...
	float thirsty = Complex_FuzzyLogicApp::m_fuzzyEngine.thirsty->getMembership(water);
	//how full are we...
	float notThirsty = Complex_FuzzyLogicApp::m_fuzzyEngine.notThirsty->getMembership(water);
	//are we very hungry?
	float veryThirsty = Complex_FuzzyLogicApp::m_fuzzyEngine.veryThirsty->getMembership(water);
	float weekFromThirst = Complex_FuzzyLogicApp::m_fuzzyEngine.WeekFromThirsty->getMembership(water);
	//how close are we to food...
	float waterRangeClose = Complex_FuzzyLogicApp::m_fuzzyEngine.veryNear->getMembership(waterRange);
	float waterRangeMedium = Complex_FuzzyLogicApp::m_fuzzyEngine.mediumRange->getMembership(waterRange);
	float waterRangeFar = Complex_FuzzyLogicApp::m_fuzzyEngine.farAway->getMembership(waterRange);
	//is this a very desirable action?
	float veryDesirableValue = Fuzzy::OR(Fuzzy::AND(waterRangeClose,thirsty),veryThirsty);
	veryDesirableValue= Fuzzy::OR(veryDesirableValue,weekFromThirst);
	//is it a desirable action?
	float desirableValue = Fuzzy::AND(Fuzzy::NOT(waterRangeClose),thirsty);
	//is in undesirable?  In this case if we are full it's undesirable
	float undesirableValue = notThirsty;
	//set up our maximum values readt to defuzzify
	float maxVeryDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.veryDesirable->getMaxMembership();
	float maxDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.desirable->getMaxMembership();
	float maxUndesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.undesirable->getMaxMembership();
	//defuzzify
	desire = maxVeryDesirable*veryDesirableValue + maxDesirable* desirableValue + maxUndesirable*undesirableValue;
	desire /= (.1f + veryDesirableValue + desirableValue + undesirableValue);
	//return our final desire
	cout << desire << endl;
	return desire;

}

//-----------------------------------------------------------
// Checks how desireable drinking is
// return (float): Returns desirablity
//-----------------------------------------------------------
float  AgentPred::checkDrinkingDesirable()
{
	float desire = 0; //this is the return value which will be how much
	//our AI desires food
	float waterRange = findNearestResource(WATER);
	float predRange = findNearestResource(PRED_AI);
	//how far is the nearest food source
	//how hungry are we...
	float thirsty = Complex_FuzzyLogicApp::m_fuzzyEngine.thirsty->getMembership(water);
	//how full are we...
	float notThirsty = Complex_FuzzyLogicApp::m_fuzzyEngine.notThirsty->getMembership(water);
	//are we very hungry?
	float veryThirsty = Complex_FuzzyLogicApp::m_fuzzyEngine.veryThirsty->getMembership(water);
	float weekFromThirst = Complex_FuzzyLogicApp::m_fuzzyEngine.WeekFromThirsty->getMembership(water);
	//how close are we to food...
	float waterRangeClose = Complex_FuzzyLogicApp::m_fuzzyEngine.veryNear->getMembership(waterRange);
	float waterRangeMedium = Complex_FuzzyLogicApp::m_fuzzyEngine.mediumRange->getMembership(waterRange);
	float waterRangeFar = Complex_FuzzyLogicApp::m_fuzzyEngine.farAway->getMembership(waterRange);
	//is this a very desirable action?
	float veryDesirableValue = Fuzzy::OR(Fuzzy::AND(waterRangeClose, thirsty), veryThirsty);
	veryDesirableValue = Fuzzy::OR(veryDesirableValue, weekFromThirst);
	//is it a desirable action?
	float desirableValue = Fuzzy::AND(Fuzzy::NOT(waterRangeClose), thirsty);
	//is in undesirable?  In this case if we are full it's undesirable
	float undesirableValue = Fuzzy::OR(notThirsty, predRange);
	//set up our maximum values readt to defuzzify
	float maxVeryDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.veryDesirable->getMaxMembership();
	float maxDesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.desirable->getMaxMembership();
	float maxUndesirable = Complex_FuzzyLogicApp::m_fuzzyEngine.undesirable->getMaxMembership();
	//defuzzify
	desire = maxVeryDesirable * veryDesirableValue + maxDesirable * desirableValue + maxUndesirable * undesirableValue;
	desire /= (.1f + veryDesirableValue + desirableValue + undesirableValue);
	//return our final desire
	cout << desire << endl;
	return desire;

}

//-----------------------------------------------------------
// Calculates the velocity for agent to move towards food
// desirability (float): How desireable?
// delta (float): How long since last frame?
// return (glm::vec2): returns velocity for agent to move
//-----------------------------------------------------------
glm::vec2 Agent::gotoFood(float desirability, float delta)
{
	glm::vec2 velocity = findResourceVector(FOOD) * delta * (1+desirability)*maxSpeed;
	return velocity;
}

//-----------------------------------------------------------
// Calculates the velocity for agent to move towards food
// desirability (float): How desireable?
// delta (float): How long since last frame?
// return (glm::vec2): returns velocity for agent to move
//-----------------------------------------------------------
glm::vec2  AgentPred::gotoFood(float desirability, float delta)
{
	glm::vec2 velocity = findResourceVector(SIMPLE_AI) * delta * (1 + desirability) * maxSpeed;
	return velocity;
}

//-----------------------------------------------------------
// Calculates the velocity for agent to move towards cave
// desirability (float): How desireable?
// delta (float): How long since last frame?
// return (glm::vec2): returns velocity for agent to move
//-----------------------------------------------------------
glm::vec2 Agent::gotoCave(float desirability, float delta)
{
	glm::vec2 velocity = findResourceVector(CAVE) * delta * (1+desirability)*maxSpeed;
	return velocity;
}

//-----------------------------------------------------------
// Calculates the velocity for agent to move towards cave
// desirability (float): How desireable?
// delta (float): How long since last frame?
// return (glm::vec2): returns velocity for agent to move
//-----------------------------------------------------------
glm::vec2  AgentPred::gotoCave(float desirability, float delta)
{
	glm::vec2 velocity = findResourceVector(CAVE) * delta * (1 + desirability) * maxSpeed;
	return velocity;
}

//-----------------------------------------------------------
// Calculates the velocity for agent to move towards water
// desirability (float): How desireable?
// delta (float): How long since last frame?
// return (glm::vec2): returns velocity for agent to move
//-----------------------------------------------------------
glm::vec2 Agent::gotoWater(float desirability, float delta)
{
	glm::vec2 velocity = findResourceVector(WATER) * delta * (1+desirability) * maxSpeed;
	return velocity;
}

//-----------------------------------------------------------
// Calculates the velocity for agent to move towards water
// desirability (float): How desireable?
// delta (float): How long since last frame?
// return (glm::vec2): returns velocity for agent to move
//-----------------------------------------------------------
glm::vec2  AgentPred::gotoWater(float desirability, float delta)
{
	glm::vec2 velocity = findResourceVector(WATER) * delta * (1 + desirability) * maxSpeed;
	return velocity;
}

//-----------------------------------------------------------
// Updates agents stats and decision making
// delta (float): How long since last frame?
//-----------------------------------------------------------
void Agent::update(float delta)
{
	float eatDesirability = checkEatingDesirable();
	float sleepDesirability = checkSleepDesirable();
	float drinkDesirability = checkDrinkingDesirable();
	glm::vec2 velocity;
	if(eatDesirability>sleepDesirability && eatDesirability>drinkDesirability)
	{
		velocity= gotoFood(eatDesirability,delta);
	}
	else if(sleepDesirability>drinkDesirability)
	{
		velocity = gotoCave(sleepDesirability,delta);
	}
	else
	{
		velocity = gotoWater(drinkDesirability,delta);
	}
	position += velocity;
	//if we are near water then drink
	if(findNearestResource(WATER) <2)
	{
		water  = 1;
	}
	//else we are using water
	else
	{
		water -= delta *.05f;
	}
	//clamp water
	if(water <0)
	{
		water = 0;
	}
	if(water >1)
	{
		water = 1;
	}
	//if we are near food then eat
	if(findNearestResource(FOOD) <2)
	{
		food += delta * .2f;
	}
	//else we get hungrier
	else
	{
		food -= delta * .03f;
	}
	//clamp food
	if(food <0)
	{
		food = 0;
	}
	if(food > 1)
	{
		food = 1;
	}
	//if we are near cave then sleep
	if(findNearestResource(CAVE) <2)
	{
		tiredness += delta * .3f;
	}
	//else we get sleepier
	else
	{
		tiredness -= delta * .02f;
	}
	//clamp tiredness
	if(tiredness <0)
	{
		tiredness = 0;
	}
	if(tiredness >1)
	{
		tiredness = 1;
	}
}

//-----------------------------------------------------------
// Updates agents stats and decision making
// delta (float): How long since last frame?
//-----------------------------------------------------------
void AgentPred::update(float delta)
{
	float eatDesirability = checkEatingDesirable();
	float sleepDesirability = checkSleepDesirable();
	float drinkDesirability = checkDrinkingDesirable();
	glm::vec2 velocity;
	if (eatDesirability > sleepDesirability && eatDesirability > drinkDesirability)
	{
		velocity = gotoFood(eatDesirability, delta);
	}
	else if (sleepDesirability > drinkDesirability)
	{
		velocity = gotoCave(sleepDesirability, delta);
	}
	else
	{
		velocity = gotoWater(drinkDesirability, delta);
	}
	position += velocity;
	//if we are near water then drink
	if (findNearestResource(WATER) < 2)
	{
		water = 1;
	}
	//else we are using water
	else
	{
		water -= delta * .05f;
	}
	//clamp water
	if (water < 0)
	{
		water = 0;
	}
	if (water > 1)
	{
		water = 1;
	}
	//if we are near food then eat
	if (findNearestResource(SIMPLE_AI) < 2)
	{
		food += delta * .2f;
	}
	//else we get hungrier
	else
	{
		food -= delta * .03f;
	}
	//clamp food
	if (food < 0)
	{
		food = 0;
	}
	if (food > 1)
	{
		food = 1;
	}
	//if we are near cave then sleep
	if (findNearestResource(CAVE) < 2)
	{
		tiredness += delta * .3f;
	}
	//else we get sleepier
	else
	{
		tiredness -= delta * .02f;
	}
	//clamp tiredness
	if (tiredness < 0)
	{
		tiredness = 0;
	}
	if (tiredness > 1)
	{
		tiredness = 1;
	}
}





//-----------------------------------------------------------
// Updates all world objects
// delta (float): How long since last frame?
//-----------------------------------------------------------
void WorldController::update(float delta)
{
	for(auto worldObject:worldObjects)
	{
		worldObject->update(delta);
	}
}

//-----------------------------------------------------------
// Draws all world objects
// spriteBatch (aie::Renderer2D*): What is the renderer used?
//-----------------------------------------------------------
void WorldController::draw(aie::Renderer2D* spriteBatch)
{
	for(auto worldObject:worldObjects)
	{
		worldObject->draw(spriteBatch);
	}
}

//-----------------------------------------------------------
// Adds new object to world
// newObject (WorldObject*): What is the new object?
//-----------------------------------------------------------
void WorldController::addObject(WorldObject* newObject)
{
	newObject->worldObjects = &worldObjects;
	worldObjects.push_back(newObject);
}





