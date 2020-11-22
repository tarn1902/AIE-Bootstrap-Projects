/*----------------------------------------
File Name: Navmesh.h
Purpose: class for navmesh
Author: ~Tarn Cooper (Mostly done through a tutorial)
Parts I personaly changed are marked with (Tarn Cooper)
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "NavMesh.h"

class NavMeshApp : public aie::Application {
public:

	NavMeshApp();
	virtual ~NavMeshApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	std::vector< GameObject*> gameObjects;
	NavMesh*			m_navMesh;
};