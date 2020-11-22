/*----------------------------------------
File Name: SceneObject.h
Purpose: Handles all basic elements of a
	     scene
Author: Tarn Cooper
Modified: 16/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <vector>
#include <assert.h>
#include "Renderer2D.h"
#include "MathsLibrarySLL.h"
#include <iostream>

// An object that is drawn on the screen
class SceneObject
{
public:
//-----------------------------------------------------------
// Constructs scene
//-----------------------------------------------------------
	SceneObject() {}
//-----------------------------------------------------------
// Destructs scene
//-----------------------------------------------------------
	~SceneObject()
	{
		// detach from parent 
		if (m_parent != nullptr) m_parent->removeChild(this);
		// remove all children 
		for (auto child : m_children)
			child->m_parent = nullptr;
	}

//-----------------------------------------------------------
// Virtual function for updating the objects transformation
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual void onUpdate(float deltaTime) { }

//-----------------------------------------------------------
// Virtual function for drawing on renderer
// renderer (aie::Renderer2D*): What renderer will it draw 
//								on?
//-----------------------------------------------------------
	virtual void onDraw(aie::Renderer2D* renderer) { }
//-----------------------------------------------------------
// virtual function Gets closest point to other point
// point (const Vec2<float>&): What is other point?
// return (Vec2<float>): Returns the closest point.
//-----------------------------------------------------------
	virtual Vec2<float> closestPoint(const Vec2<float>& p) { return Vec2<float>(0, 0); };
//-----------------------------------------------------------
// Virtual function for checking if collision occured
// other (SceneObject*): What is other object?
// return (bool): Returns true if collsion occured
//-----------------------------------------------------------
	virtual bool CheckCollision(SceneObject*) { return false; };
//-----------------------------------------------------------
// Function for updating all objects in this object
// deltaTime (float): how long since last update
//-----------------------------------------------------------
	void update(float deltaTime) {
		// run onUpdate behaviour 
		onUpdate(deltaTime);
		// update children 
		for (auto child : m_children)
			child->update(deltaTime);
	}
//-----------------------------------------------------------
// Function for setting a new direction to class.
// inDirection (Vec2<float>): What direction is this object?
//-----------------------------------------------------------
	void setDirection(Vec2<float> inDirection) { direction = inDirection; }

//-----------------------------------------------------------
// Sets value if object is constantly rotating
// radians(float): How quickly will it rotate
//-----------------------------------------------------------
	void setConstRotation(float radians) { rotation = radians; }

//-----------------------------------------------------------
// Gets current speed of object
// return (float): Returns speed of object						  
//-----------------------------------------------------------
	float getSpeed()
	{
		return speed;
	}

//-----------------------------------------------------------
// Function for drawing all objects in this object
// renderer (aie::Renderer2D*): draws all objects within this
//							    object
//-----------------------------------------------------------
	void draw(aie::Renderer2D* renderer)
	{
		onDraw(renderer);
		// draw children 
		for (auto child : m_children)
			child->draw(renderer);
	}
//-----------------------------------------------------------
// Function parent of this object
// return (SceneObject*): returns pointer to parent
//-----------------------------------------------------------
	SceneObject* getParent() const
	{
		return m_parent;
	}
//-----------------------------------------------------------
// Function getting size of list
// return (size_t): returns size
//-----------------------------------------------------------
	size_t childCount() const
	{
		return m_children.size();
	}
//-----------------------------------------------------------
// Function getting specific child from list.
// index (unsigned int): Where is child in list?
// return (std::vector<SceneObject*>): returns child
//-----------------------------------------------------------
	SceneObject* getChild(unsigned int index) const
	{
		return m_children[index];
	}
//-----------------------------------------------------------
// Function getting list of children of object
// return (std::vector<SceneObject*>): returns list of 
//									   children
//-----------------------------------------------------------
	std::vector<SceneObject*> getChildren() const
	{
		return m_children;
	}
//-----------------------------------------------------------
// Function for adding children from object
// child (SceneObject*): Which child to add?
//-----------------------------------------------------------
	void addChild(SceneObject* child)
	{
		// make sure it doesn't have a parent already 
		assert(child->m_parent == nullptr);
		// assign "this as parent 
		child->m_parent = this;
		// add new child to collection 
		m_children.push_back(child);
	}
//-----------------------------------------------------------
// Function for removing children from object
// child (SceneObject*): Which child to remove?
//-----------------------------------------------------------
	void removeChild(SceneObject* child)
	{
		// find the child in the collection 
		auto iter = std::find(m_children.begin(), m_children.end(), child);
		// if found, remove it 
		if (iter != m_children.end())
		{
			m_children.erase(iter);
			// also unassign parent 
			child->m_parent = nullptr;
			delete child;
		}
	}

//-----------------------------------------------------------
// Function for getting current direction of class.
// returns(Vec2<float>): Returns direction of class object.
//-----------------------------------------------------------
	Vec2<float> getDirection()
	{
		return direction;
	}

//-----------------------------------------------------------
// Function to get local transform of this object
//-----------------------------------------------------------
	const Mat3<float>& getLocalTransform() const
	{
		return m_localTransform;
	}
//-----------------------------------------------------------
// Function to get global transform of this object
//-----------------------------------------------------------
	const Mat3<float>& getGlobalTransform() const
	{
		return m_globalTransform;
	}
//-----------------------------------------------------------
// Function for setting parent global transforms to local 
// transforms or children of it to global transforms 
// multiplied by local transforms.
//-----------------------------------------------------------
	void updateTransform()
	{
		if (m_parent != nullptr)
			m_globalTransform = m_parent->m_globalTransform * m_localTransform;
		else
			m_globalTransform = m_localTransform;
		for (auto child : m_children)
			child->updateTransform();
	}
//-----------------------------------------------------------
// Function for setting local transforms position
// x (float): Where to place horizontally?
// y (float): Where to place vertically?
//-----------------------------------------------------------
	void setPosition(float x, float y)
	{
		m_localTransform[2] = { x, y, 1 };
		updateTransform();
	}
//-----------------------------------------------------------
// Function for setting local transforms translation
// x (float): How much to move horizontaly?
// y (float): How much to move vertically?
//-----------------------------------------------------------
	void translate(float x, float y)
	{
		m_localTransform.translate(x, y);
		updateTransform();
	}
//-----------------------------------------------------------
// Function for setting local transforms rotation
// radians (float): how much to rotate?
//-----------------------------------------------------------
	void rotate(float radians)
	{
		m_localTransform.rotateZ(radians);
		updateTransform();
	}

//-----------------------------------------------------------
// Function for setting local transforms scale
// width (float): How much wider?
// height (float): How much taller?
//-----------------------------------------------------------
	void scale(float width, float height)
	{
		m_localTransform.scale(width, height, 1);
		updateTransform();
	}
//-----------------------------------------------------------
// Function for getting ray range of class.
// returns(Vec2<float>): Returns ray range
//-----------------------------------------------------------
	float getRayRange()
	{
		return rayRange;
	}

protected:
	Vec2<float> direction;				//direction of object
	float speed = 0;					//speed of object
	float rayRange = 0;					//range of ray
	float rotation = 0;					//rotation pace
	SceneObject* m_parent = nullptr;	//pointer to parent of this object
	std::vector<SceneObject*> m_children; //list of children of this object
	Mat3<float> m_localTransform = Mat3<float>();	//transformation of this object
	Mat3<float> m_globalTransform = Mat3<float>();	//transformation of highest parent
};