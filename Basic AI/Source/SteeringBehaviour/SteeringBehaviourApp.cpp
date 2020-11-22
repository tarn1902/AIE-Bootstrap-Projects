#include "SteeringBehaviourApp.h"
#include "KeyboardBehaviour.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "ArriveBehaviour.h"
#include "PursueBehaviour.h"
#include "EvadeBehaviour.h"
#include "WanderBehaviour.h"
#include "CollisionAvoidBehaviour.h"
#include "FlockBehaviour.h"
#include "Box.h"
#include "Circle.h"
#include "Texture.h"
#include "Font.h"
#include <time.h>
#include "Input.h"


SteeringBehaviourApp::SteeringBehaviourApp() {
	srand((unsigned int)time(nullptr));
}

SteeringBehaviourApp::~SteeringBehaviourApp() {

}

bool SteeringBehaviourApp::startup()
{
	m_2dRenderer = new aie::Renderer2D(); 
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_player = new Agent();
	m_player->AddBehaviour(new KeyboardBehaviour());
	m_player->SetPosition(Vector2(getWindowWidth() * 0.5f, getWindowHeight() * 0.5f));

	for (int i = 0; i < 10; i++)
	{
		Box* box = new Box();
		box->minPos = Vector2((float)(rand() % 1280), (float)(rand() % 720));
		box->lengthX = 20;
		box->lengthY = 20;
		box->maxPos = Vector2(box->minPos.x + box->lengthX, box->minPos.y + box->lengthY);
		box->maxRadius = sqrt(box->lengthX * box->lengthX + box->lengthY * box->lengthY);
		objects.push_back(box);

		Circle* circle = new Circle();
		circle->Center = Vector2((float)(rand() % 1280), (float)(rand() % 720));
		circle->radius = 20;
		objects.push_back(circle);
	}

	for (int i = 0; i < 10; i++)
	{
		Agent* agent = new Agent();
		agent->SetTarget(m_player);
		agent->SetPosition(Vector2(Vector2((float)(rand() % 1280), (float)(rand() % 720))));
		agent->SetObjects(objects);
		agents.push_back(agent);
	}

	for each (Agent* agent in agents)
	{
		agent->SetAgents(agents);
	}

	return true;
}

void SteeringBehaviourApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	for each (Object* object in objects)
	{
		delete object;
	}
	for each (Agent* agent in agents)
	{
		delete agent;
	}
}

void SteeringBehaviourApp::update(float deltaTime) {
	
	// input example
	aie::Input* input = aie::Input::getInstance();
	if (input->wasKeyPressed(aie::INPUT_KEY_1))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new SeekBehaviour);
			objectsVisible = false;
		}		
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_2))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new FleeBehaviour);
			objectsVisible = false;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_3))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new ArriveBehaviour);
			objectsVisible = false;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_4))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new PursueBehaviour);
			objectsVisible = false;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_5))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new EvadeBehaviour);
			objectsVisible = false;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_6))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new CollisionAvoidBehaviour);
			objectsVisible = true;
		}
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_7))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new WanderBehaviour);
			objectsVisible = false;
		}
	}

	if (input->wasKeyPressed(aie::INPUT_KEY_8))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new KeyboardBehaviour);
			objectsVisible = false;
		}
	}
	if (input->wasKeyPressed(aie::INPUT_KEY_9))
	{
		for each (Agent* agent in agents)
		{
			agent->RemoveBehaviours();
			agent->AddBehaviour(new FlockBehaviour);
			objectsVisible = false;
		}
	}
	m_player->Update(deltaTime);
	for each (Agent* agent in agents)
	{
		agent->Update(deltaTime);
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void SteeringBehaviourApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	m_player->Draw(m_2dRenderer);
	for each (Agent* agent in agents)
	{
		agent->Draw(m_2dRenderer);
	}

	if (objectsVisible)
	{
		for each (Object* object in objects)
		{
			if (static_cast<Circle*>(object)->shape == 'C')
			{
				Circle* circle = static_cast<Circle*>(object);
				m_2dRenderer->drawCircle(circle->Center.x, circle->Center.y, circle->radius);
			}
			else if (static_cast<Box*>(object)->shape == 'B')
			{
				Box* box = static_cast<Box*>(object);
				m_2dRenderer->drawBox(box->minPos.x, box->minPos.y, box->lengthX, box->lengthY);
			}
		}
	}
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}