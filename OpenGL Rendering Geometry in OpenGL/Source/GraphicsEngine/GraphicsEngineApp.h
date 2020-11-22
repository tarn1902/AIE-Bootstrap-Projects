/*----------------------------------------
File Name: GraphicEngineApp.h
Purpose: Structure of Graphic Engine App class
Author: Tarn Cooper
Modified: 17 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "FlyCamera.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"

//Graphic Engine App Class
class GraphicsEngineApp : public aie::Application {
public:

	GraphicsEngineApp();
	virtual ~GraphicsEngineApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	// camera transforms
	FlyCamera* camera;

	aie::ShaderProgram shader;
	
	aie::OBJMesh bunnyMesh;
	aie::OBJMesh buddhaMesh;
	aie::OBJMesh dragonMesh;
	aie::OBJMesh lucyMesh;

	Mesh quadMesh;
	Mesh boxMesh;
	Mesh cylinderMesh;
	Mesh pyramidMesh;
	Mesh coneMesh;
	Mesh gridMesh;
	Mesh sphereMesh;

	glm::mat4 buddhaTransform;
	glm::mat4 bunnyTransform;
	glm::mat4 dragonTransform;
	glm::mat4 lucyTransform;
	glm::mat4 boxTransform;
	glm::mat4 cylinderTransform;
	glm::mat4 quadTransform;
	glm::mat4 pyramidTransform;
	glm::mat4 coneTransform;
	glm::mat4 gridTransform;
	glm::mat4 sphereTransform;
};