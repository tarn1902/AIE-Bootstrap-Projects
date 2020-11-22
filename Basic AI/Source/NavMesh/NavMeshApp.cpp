/*----------------------------------------
File Name: Navmesh.h
Purpose: functions of NavMeshApp.
Author: ~Tarn Cooper (Mostly done through a tutorial)
Parts I personaly changed are marked with (Tarn Cooper)
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "NavMeshApp.h"
#include "Font.h"
#include "Input.h"
#include "BehaviourTree.h"
#include "Selector.h"

NavMeshApp::NavMeshApp() {

}

NavMeshApp::~NavMeshApp() {

}

bool NavMeshApp::startup() {
	m_navMesh = new NavMesh(1280, 720);
	gameObjects.push_back(new GameObject());
	gameObjects.push_back(new GameObject());
	gameObjects.push_back(new GameObject());
	m_2dRenderer = new aie::Renderer2D();
	//Personal Behaviour Tree (Tarn Cooper)
	for each (GameObject* gameObject in gameObjects)
	{
		gameObject->position.x = (float)(rand() % 1280);
		gameObject->position.x = (float)(rand() % 720);
		Selector* pathSelect = new Selector();
		BehaviourTree* tree = new BehaviourTree();
		pathSelect->children.push_back(new NavMesh::FollowPathBehaviour());
		pathSelect->children.push_back(new NavMesh::NewPathBehaviour(m_navMesh, gameObject->smoothPath));
		tree->root = pathSelect;
		gameObject->behaviour = tree;
	}
	
	// just to help mess with the random
	srand(42);

	// random obstacles
	for (int i = 0; i < 12; ++i) {

		bool safe = false;
		do {
			safe = m_navMesh->addObstacle(rand() / float(RAND_MAX) * getWindowWidth() * 0.75f + getWindowWidth() * 0.125f,
										  rand() / float(RAND_MAX) * getWindowHeight() * 0.75f + getWindowHeight() * 0.125f,
										  60, 60,
										  10);
		} while (safe == false);
	}

	m_navMesh->build();

	return true;
}

void NavMeshApp::shutdown() {

	delete m_navMesh;

	delete m_2dRenderer;
}

void NavMeshApp::update(float deltaTime) {
	
	// input example
	aie::Input* input = aie::Input::getInstance();
	//GameObject update (Tarn Cooper)
	for each (GameObject* gameObject in gameObjects)
	{
		gameObject->behaviour->execute(gameObject, deltaTime);
	}
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void NavMeshApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	m_2dRenderer->setRenderColour(1, 1, 1);
	//GameObject draw (Tarn Cooper)
	for each (GameObject* gameObject in gameObjects)
	{
		m_2dRenderer->drawBox(gameObject->position.x, gameObject->position.y, 20, 20);
	}
	// draw nav mesh polygons
	for (auto node : m_navMesh->getNodes()) {

		m_2dRenderer->setRenderColour(1, 1, 0);
		m_2dRenderer->drawLine(node->vertices[0].x, node->vertices[0].y, node->vertices[1].x, node->vertices[1].y);
		m_2dRenderer->drawLine(node->vertices[1].x, node->vertices[1].y, node->vertices[2].x, node->vertices[2].y);
		m_2dRenderer->drawLine(node->vertices[2].x, node->vertices[2].y, node->vertices[0].x, node->vertices[0].y);
	}

	// draw obstacles
	m_2dRenderer->setRenderColour(1, 0, 0);
	for (auto& o : m_navMesh->getObstacles()) {
		m_2dRenderer->drawBox(o.x + o.w * 0.5f, o.y + o.h * 0.5f, o.w, o.h);
	}

	

	// done drawing sprites
	m_2dRenderer->end();
}