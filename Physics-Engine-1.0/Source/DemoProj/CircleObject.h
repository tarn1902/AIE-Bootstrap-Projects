/*----------------------------------------
File Name: CircleObject.h
Purpose: Handles physics of texture as if
it was a circle
Author: Tarn Cooper
Modified: 13/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "SceneObject.h"
//A class that inherits from sceneObject to control physics of the circle
class CircleObject : public SceneObject
{
public:
//-----------------------------------------------------------
// Constructs Circle object
// inTexture(aie::Texture*): What texture to use?
// inSpeed (float): how fast is this moving?
//-----------------------------------------------------------
	CircleObject(aie::Texture* inTexture, float inSpeed);
//-----------------------------------------------------------
// Destroys Circle object
//-----------------------------------------------------------
	virtual ~CircleObject() {};
//-----------------------------------------------------------
// Gets radius of circle
// returns(float): Returns radius of circle
//----------------------------------------------------------
	float getRadius();
//-----------------------------------------------------------
// Virtual function for drawing on renderer
// renderer (aie::Renderer2D*): What renderer will it draw 
//								on?
//-----------------------------------------------------------
	void onDraw(aie::Renderer2D* renderer) override;
//-----------------------------------------------------------
// Virtual function for updating the objects transformation
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
	void onUpdate(float deltaTime) override;
//-----------------------------------------------------------
// Virtual function for checking if collision occured
// other (SceneObject*): What is other object?
// return (bool): Returns true if collsion occured
//-----------------------------------------------------------
	virtual bool CheckCollision(SceneObject* other) override;
//-----------------------------------------------------------
// Gets center of object as a point
// return (Vec2<float>): Returns point in center.						  
//-----------------------------------------------------------
	Vec2<float> Center() const;
//-----------------------------------------------------------
// virtual function Gets closest point to other point
// point (const Vec2<float>&): What is other point?
// return (Vec2<float>): Returns the closest point.
//-----------------------------------------------------------
	virtual Vec2<float> closestPoint(const Vec2<float>& point) override;


protected:
	float radius;						//radius of circle
	aie::Texture* m_texture = nullptr;	//texture of object
};