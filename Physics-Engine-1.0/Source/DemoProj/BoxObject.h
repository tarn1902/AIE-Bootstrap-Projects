/*----------------------------------------
File Name: BoxObject.h
Purpose: Handles physics of texture as if 
it was a box
Author: Tarn Cooper
Modified: 12/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "SceneObject.h"
//A class that inherits from sceneObject to control physics of the box
class BoxObject : public SceneObject
{
public:
//-----------------------------------------------------------
// Constructs Box object
// inTexture(aie::Texture*): What texture to use?
// inSpeed (float): How fast is this moving?
//-----------------------------------------------------------
	BoxObject(aie::Texture* inTexture, float inSpeed);

//-----------------------------------------------------------
// Destroys Box object
//-----------------------------------------------------------
	virtual ~BoxObject() {};

//-----------------------------------------------------------
// Gets vector of maximum point of object
// returns(Vec2<float>): Returns maximum of box point
//-----------------------------------------------------------
	Vec2<float> getMaxPoint();

//-----------------------------------------------------------
// Gets vector of minmum point of object
// returns(Vec2<float>): Returns minimum of box point
//-----------------------------------------------------------
	Vec2<float> getMinPoint();

//-----------------------------------------------------------
// Gets vector of forward direction
// returns(Vec2<float>): Returns forward direction of object
//-----------------------------------------------------------
	Vec2<float> getForwardDirection();

//-----------------------------------------------------------
// Virtual function for drawing on renderer
// renderer (aie::Renderer2D*): What renderer will it draw 
//								on?
//-----------------------------------------------------------
	virtual void onDraw(aie::Renderer2D* renderer) override;

//-----------------------------------------------------------
// Virtual function for updating the objects transformation
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	virtual void onUpdate(float deltaTime) override;

//-----------------------------------------------------------
// Virtual function for checking if collision occured
// other (SceneObject*): What is other object?
// return (bool): Returns true if collsion occured
//-----------------------------------------------------------
	virtual bool CheckCollision(SceneObject* other) override;

//-----------------------------------------------------------
// virtual function Gets closest point to other point
// point (const Vec2<float>&): What is other point?
// return (Vec2<float>): Returns the closest point.
//-----------------------------------------------------------
	virtual Vec2<float> closestPoint(const Vec2<float>& point) override;
//-----------------------------------------------------------
// Gets vector of each corner on object
// return (std::vector<Vec2<float>>): Returns all corners in 
//									  list point.							  
//-----------------------------------------------------------
	std::vector<Vec2<float>> getCorners() const;

//-----------------------------------------------------------
// Gets center of object as a point
// return (Vec2<float>): Returns point in center.						  
//-----------------------------------------------------------
	Vec2<float> Center() const;

protected:
	Vec2<float> m_min;					//minimum point of object
	Vec2<float> m_max;					//maximum point of object
	aie::Texture* m_texture = nullptr;	//texture of object
};