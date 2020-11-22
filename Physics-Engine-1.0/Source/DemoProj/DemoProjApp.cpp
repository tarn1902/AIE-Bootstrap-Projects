/*----------------------------------------
File Name: DemoProjApp.cpp
Purpose: Holds methods of DemoProjApp.h
Author: Tarn Cooper
Modified: 16/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "DemoProjApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "BoxObject.h"
#include "CircleObject.h"
#include "PlanesObject.h"

//-----------------------------------------------------------
// Constructs application
//-----------------------------------------------------------
DemoProjApp::DemoProjApp() {

}
//-----------------------------------------------------------
// Destructs application
//-----------------------------------------------------------
DemoProjApp::~DemoProjApp() {

}

//-----------------------------------------------------------
// Controls how application starts up 
//-----------------------------------------------------------
bool DemoProjApp::startup() {
	
	
	m_2dRenderer = new aie::Renderer2D(); //Creates new renderer
	sceneObject = new SceneObject(); //Creates new scene
	sceneObject->setPosition(0, 0); //sets center to position 0,0
	m_font = new aie::Font("../bin/font/consolas.ttf", 32); //Creates new font

	//Creates new textures
	tankTex = new aie::Texture("../bin/textures/tankGreen.png");
	ballTex = new aie::Texture("../bin/textures/ball.png");
	emptyTex = new aie::Texture("");
	barrelTex = new aie::Texture("../bin/textures/barrelGreen.png");

	//Spawns Tank in scene
	BoxObject* tankObject = new BoxObject(tankTex, 0);
	BoxObject* emptyObject = new BoxObject(emptyTex, 0);
	BoxObject* barrelObject = new BoxObject(barrelTex, 0);
	BoxObject* emptyObject2 = new BoxObject(emptyTex, 0);
	sceneObject->addChild(tankObject);
	tankObject->addChild(emptyObject);
	emptyObject->addChild(barrelObject);
	barrelObject->translate(0, 20);
	emptyObject->addChild(emptyObject2);
	emptyObject2->translate(0, 100);
	tankObject->setPosition((float)getWindowWidth() / 2, (float)getWindowHeight()/5);

	//Creates barriers in scene for objects to collide with
	sceneObject->addChild(new PlanesObject(-1, 0, (float)getWindowWidth()));
	sceneObject->addChild(new PlanesObject(0, -1, (float)getWindowHeight()));
	sceneObject->addChild(new PlanesObject(0, 1, 0));
	sceneObject->addChild(new PlanesObject(1, 0, 0));

	return true;
}

//-----------------------------------------------------------
// Controls how application shuts down
//-----------------------------------------------------------
void DemoProjApp::shutdown() {

	delete m_font;	//deletes font
	delete m_2dRenderer; //deletes renderer
	delete sceneObject; //deletes scene

	//deletes textures
	delete 	tankTex; 
	delete ballTex;
	delete emptyTex;
	delete barrelTex;
}
//-----------------------------------------------------------
// Updates data between frames
// deltaTime (float): How much time has passed from last 
//					  frame?
//-----------------------------------------------------------
void DemoProjApp::update(float deltaTime) {

	aie::Input* input = aie::Input::getInstance();

	//moves tank to left
	if (input->isKeyDown(aie::INPUT_KEY_A))
	{
		sceneObject->getChild(0)->translate(-2, 0);
	}
	//moves tank to right
	if (input->isKeyDown(aie::INPUT_KEY_D))
	{
		sceneObject->getChild(0)->translate(2, 0);
	}
	//moves tank forward
	if (input->isKeyDown(aie::INPUT_KEY_W))
	{
		sceneObject->getChild(0)->translate(0, 2);
	}
	//moves tank back
	if (input->isKeyDown(aie::INPUT_KEY_S))
	{
		sceneObject->getChild(0)->translate(0, -2);
	}

	//Fires pellet from tank
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		if (shapeMode) //changes what is fired
		{
			CircleObject* circleObject = new CircleObject(ballTex, speed);
			sceneObject->addChild(circleObject);
			circleObject->setDirection(dynamic_cast<BoxObject*>(sceneObject->getChild(0)->getChild(0))->getForwardDirection());
			circleObject->setPosition(sceneObject->getChild(0)->getChild(0)->getChild(1)->getGlobalTransform().zAxis.x, sceneObject->getChild(0)->getChild(0)->getChild(1)->getGlobalTransform().zAxis.y);
		}
		else
		{
			//test tank spawn
			BoxObject* tankObject = new BoxObject(tankTex, 0);
			BoxObject* emptyObject = new BoxObject(emptyTex, 0);
			BoxObject* barrelObject = new BoxObject(barrelTex, 0);
			BoxObject* emptyObject2 = new BoxObject(emptyTex, 0);
			sceneObject->addChild(tankObject);
			tankObject->addChild(emptyObject);
			emptyObject->addChild(barrelObject);
			barrelObject->translate(0, 20);
			emptyObject->addChild(emptyObject2);
			emptyObject2->translate(0, 100);
			emptyObject->setConstRotation(0.5);
			//tankObject->setDirection(dynamic_cast<BoxObject*>(sceneObject->getChild(0)->getChild(0))->getForwardDirection());
			tankObject ->setPosition(sceneObject->getChild(0)->getChild(0)->getChild(1)->getGlobalTransform().zAxis.x, sceneObject->getChild(0)->getChild(0)->getChild(1)->getGlobalTransform().zAxis.y);
		}
	}

	//Changes mode
	if (input->wasKeyPressed(aie::INPUT_KEY_M))
	{
		shapeMode = !shapeMode;
	}

	//Resets level
	if (input->wasKeyPressed(aie::INPUT_KEY_R))
	{
		
		for (auto child : sceneObject->getChildren())
		{ 
			sceneObject->removeChild(child);
		}
		//Spawn Tank
		BoxObject* tankObject = new BoxObject(tankTex, 0);
		BoxObject* emptyObject = new BoxObject(emptyTex, 0);
		BoxObject* barrelObject = new BoxObject(barrelTex, 0);
		BoxObject* emptyObject2 = new BoxObject(emptyTex, 0);
		sceneObject->addChild(tankObject);
		tankObject->addChild(emptyObject);
		emptyObject->addChild(barrelObject);
		barrelObject->translate(0, 20);
		emptyObject->addChild(emptyObject2);
		emptyObject2->translate(0, 100);
		tankObject->setPosition((float)getWindowWidth() / 2, (float)getWindowHeight() / 5);

		//Create barrier for objects
		sceneObject->addChild(new PlanesObject(-1, 0, (float)getWindowWidth()));
		sceneObject->addChild(new PlanesObject(0, -1, (float)getWindowHeight()));
		sceneObject->addChild(new PlanesObject(0, 1, 0));
		sceneObject->addChild(new PlanesObject(1, 0, 0));
	}

	//Changes rotation of turret on tank to right
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		sceneObject->getChild(0)->getChild(0)->rotate(-deltaTime);
	}

	//Changes rotation of turret on tank to left
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		sceneObject->getChild(0)->getChild(0)->rotate(+deltaTime);
	}

	sceneObject->update(deltaTime);
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}
	//-----------------------------------------------------------
	// Draw images on screen
	//-----------------------------------------------------------
void DemoProjApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	sceneObject->draw(m_2dRenderer);	

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 10);
	m_2dRenderer->drawText(m_font, "Press arrows to rotate gun", 800, 150);
	m_2dRenderer->drawText(m_font, "Press Spacebar to fire gun", 800, 115);
	m_2dRenderer->drawText(m_font, "Press WASD to move", 800, 80);
	m_2dRenderer->drawText(m_font, "Press R to reset", 800, 45);
	m_2dRenderer->drawText(m_font, "Press M to change gun mode",800, 10);

	// done drawing sprites
	m_2dRenderer->end();
}