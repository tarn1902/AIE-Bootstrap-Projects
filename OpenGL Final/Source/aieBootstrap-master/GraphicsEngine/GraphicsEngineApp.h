/*----------------------------------------
File Name: GraphicEngineApp.h
Purpose: Structure of Graphic Engine App class
Author: Tarn Cooper
Modified: 19 April 2020
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
#include "RenderTarget.h"
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
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	FlyCamera* camera;

	aie::ShaderProgram shader;
	aie::ShaderProgram postShader;

	aie::Texture gridTexture;

	aie::OBJMesh	spearMesh;
	aie::OBJMesh	catMesh;

	Mesh fullscreenQuad;

	Mesh quadMesh;

	glm::mat4	quadTransform;
	glm::mat4	spearTransform;
	glm::mat4	catTransform;

	struct Light {
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

	};
	struct PointLight {
		glm::vec3 position;

		float constant;
		float linear;
		float quadratic;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	Light lightDir;
	PointLight lightPoint;

	aie::RenderTarget renderTarget;
};