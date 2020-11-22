/*----------------------------------------
File Name: Agent.h
Purpose: Class for AI behaviour
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
namespace aie
{
	class Renderer2D;
}
class Behaviour;
class Object;
#include <vector>
#include "..\MathsLibrarySLL\MathsLibrarySLL.h"
typedef Vec2<float> Vector2;


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
// Updates velocity and position through AI behaviours
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual void Update(float deltaTime);
//-----------------------------------------------------------
// Draw Agent at current position
// renderer (aie::Renderer2D*): How is it being drawn?
//-----------------------------------------------------------
	virtual void Draw(aie::Renderer2D* renderer);
//-----------------------------------------------------------
// Adds new behaviour to list of behaviours
// behaviour (Behaviour*): How is it being drawn?
//-----------------------------------------------------------
	void AddBehaviour(Behaviour* behaviour);
//-----------------------------------------------------------
// Removes all behaviours from list of behaviours
//-----------------------------------------------------------
	void RemoveBehaviours();
//-----------------------------------------------------------
// Sets current position of agent
// position (Vector2): Where is it's current position?
//-----------------------------------------------------------
	void SetPosition(Vector2 position);
//-----------------------------------------------------------
// Gets current position of agent
// Return (Vector2): Returns current position
//-----------------------------------------------------------
	Vector2 GetPosition();
//-----------------------------------------------------------
// Sets current velocity of agent
// velocity (Vector2): What is the current velocity of agent?
//-----------------------------------------------------------
	void SetVelocity(Vector2 velocity);
//-----------------------------------------------------------
// Gets current velocity of agent
// Return (Vector2): Returns current velocity
//-----------------------------------------------------------
	Vector2 GetVelocity();
//-----------------------------------------------------------
// Sets list of all agents in scene
// inAgents (std::vector<Agent*>): What are all the agents?
//-----------------------------------------------------------
	void SetAgents(std::vector<Agent*> inAgents);
//-----------------------------------------------------------
// Gets list of all agents in scene
// Return (std::vector<Agent*>): Returns list of agents
//-----------------------------------------------------------
	std::vector<Agent*> getAgents();
//-----------------------------------------------------------
// Sets list of all objects in scene
// inAgents (std::vector<Object*>): What are all the objects?
//-----------------------------------------------------------
	void SetObjects(std::vector<Object*> inObjects);
//-----------------------------------------------------------
// Gets list of all objects in scene
// Return (std::vector<Object*>): Returns list of agents
//-----------------------------------------------------------
	std::vector<Object*> getObjects();
//-----------------------------------------------------------
// Sets current target of behaviours
// agent (Agent*): What is current target of behaviour?
//-----------------------------------------------------------
	void SetTarget(Agent* agent);
//-----------------------------------------------------------
// gets current target of behaviours
// return (Agent*): Returns target of behaviour
//-----------------------------------------------------------
	Agent* GetTarget();
protected:
	std::vector<Behaviour*> m_BehaviourList;
	Vector2 m_Position;
	Vector2 m_Velocity;
	std::vector<Agent*> agents;
	std::vector<Object*> objects;
	Agent* m_target;
};
