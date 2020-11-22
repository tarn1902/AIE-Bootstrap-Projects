/*----------------------------------------
File Name: GraphicEngineApp.cpp
Purpose: Functions of Graphic Engine App class
Author: Tarn Cooper
Modified: 18 April 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "GraphicsEngineApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>


using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

//-----------------------------------------------------------
// Constructs graphic engine app
//-----------------------------------------------------------
GraphicsEngineApp::GraphicsEngineApp() {

}

//-----------------------------------------------------------
// Destructs graphic engine app
//-----------------------------------------------------------
GraphicsEngineApp::~GraphicsEngineApp() {

}

//-----------------------------------------------------------
// Starts up graphic engine app
//-----------------------------------------------------------
bool GraphicsEngineApp::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);
	camera = new FlyCamera();
	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	lightDir.diffuse = { 1, 1, 0 };
	lightDir.specular = { 1, 1, 0 };
	lightDir.ambient = { 0.25f, 0.25f, 0.25f };

	lightPoint.diffuse = { 0, 1, 1 };
	lightPoint.specular = { 1, 1, 0 };
	lightPoint.ambient = { 0.25f, 0.25f, 0.25f };

	lightPoint.constant = 1.0f;
	lightPoint.quadratic = 0;
	lightPoint.linear = 0;

	// create simple camera transforms
	camera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	camera->SetLookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	camera->SetSpeed(10);

	shader.loadShader(aie::eShaderStage::VERTEX, "../bin/Shader/phongTextureNormalMap.vert");
	shader.loadShader(aie::eShaderStage::FRAGMENT, "../bin/Shader/phongTextureNormalMap.frag");



	if (shader.link() == false)
	{
		printf("Shader Error: %s\n", shader.getLastError());
		return false;
	}

	if (gridTexture.load("../bin/textures/numbered_grid.tga") == false) {
		printf("Failed to load texture!\n");
		return false;
	}

	if (renderTarget.initialise(1, getWindowWidth(),
		getWindowHeight()) == false) {
		printf("Render Target Error!\n");
		return false;
	}

	if (spearMesh.load("../bin/Models/soulspear/soulspear.obj", true, true) == false)
	{
		printf("Soulspear Mesh Error!\n");
		return false;
	}
	if (catMesh.load("../bin/Models/Cat/12221_Cat_v1_l3.obj", true, true) == false)
	{
		printf("cat Mesh Error!\n");
		return false;
	}
	quadMesh.InitialiseQuad(5, 5);
	quadTransform = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
	};
	spearTransform = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
	};
	catTransform = {
	0.1,0,0,0,
	0 ,0.1,0,0,
	0,0,0.1,0,
	0,4,0,1
	};

	// create a fullscreen quad
	fullscreenQuad.InitialiseFullscreenQuad();
	// load a post-processing shader
	postShader.loadShader(aie::eShaderStage::VERTEX, "../bin/Shader/post.vert");
	postShader.loadShader(aie::eShaderStage::FRAGMENT,"../bin/Shader/post.frag");
	if (postShader.link() == false) {
		printf("Post Shader Error: %s\n",
			postShader.getLastError());
		return false;
	}


	return true;
}


//-----------------------------------------------------------
// Destroys pointers on shutdown
//-----------------------------------------------------------
void GraphicsEngineApp::shutdown() {

	Gizmos::destroy();
}

//-----------------------------------------------------------
// Updates graphic engine app each frame
// deltaTime (float): What is the deltaTime?
//-----------------------------------------------------------
void GraphicsEngineApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// query time since application started
	float time = getTime();
	// rotate light
	lightDir.direction = glm::normalize(vec3(glm::cos(time/2),
		glm::sin(time/2), 0));

	//light.direction = { 0, 1, 0 };

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));
	camera->Update(deltaTime);
	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//-----------------------------------------------------------
// Draws objects on screen
//-----------------------------------------------------------
void GraphicsEngineApp::draw() {

	// wipe the screen to the background colour
	renderTarget.bind();

	clearScreen();

	shader.bind();

	// bind light
	shader.bindUniform("dirLights[0].LightDirection", lightDir.direction);
	shader.bindUniform("dirLights[0].Ia", lightDir.ambient);
	shader.bindUniform("dirLights[0].Id", lightDir.diffuse);
	shader.bindUniform("dirLights[0].Is", lightDir.specular);

	// bind light
	shader.bindUniform("pointLights[0].position", lightPoint.position);

	shader.bindUniform("pointLights[0].Ia", lightPoint.ambient);
	shader.bindUniform("pointLights[0].Id", lightPoint.diffuse);
	shader.bindUniform("pointLights[0].Is", lightPoint.specular);

	shader.bindUniform("pointLights[0].constant", lightPoint.constant);
	shader.bindUniform("pointLights[0].quadratic", lightPoint.quadratic);
	shader.bindUniform("pointLights[0].linear", lightPoint.linear);

	//bind camera position
	shader.bindUniform("cameraPosition", glm::vec3(camera->GetWorldTransform()[3].x, camera->GetWorldTransform()[3].y, camera->GetWorldTransform()[3].z));
	
	shader.bindUniform("useDiffuse", true);
	shader.bindUniform("useSpecular", false);
	shader.bindUniform("useNormal", false);

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * catTransform);
	shader.bindUniform("ModelMatrix", catTransform);
	shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(catTransform)));
	
	catMesh.draw();

	shader.bindUniform("useDiffuse", true);
	shader.bindUniform("useSpecular", true);
	shader.bindUniform("useNormal", true);

	shader.bindUniform("ProjectionViewModel", camera->GetProjectView() * spearTransform);
	shader.bindUniform("ModelMatrix", spearTransform);
	shader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(spearTransform)));
	
	spearMesh.draw();

	renderTarget.unbind();

	clearScreen();
	
	postShader.bind();
	postShader.bindUniform("blur", true);
	postShader.bindUniform("colourTarget", 0);
	renderTarget.getTarget(0).bind(0);
	fullscreenQuad.Draw();

	Gizmos::draw(camera->GetProjectView());
	Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
}