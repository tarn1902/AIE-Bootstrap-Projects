/*----------------------------------------
File Name: BinaryTreeApp.h
Purpose: Controls how the application behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "BinaryTree.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "imgui.h"

//-----------------------------------------------------------
// Object for controling the application
//-----------------------------------------------------------
class BinaryTreeApp : public aie::Application {
public:

	BinaryTreeApp();
	virtual ~BinaryTreeApp();
	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();

	
protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	BinaryTree<int>		m_binaryTree;
	TreeNode<int>*		m_selectedNode;
};