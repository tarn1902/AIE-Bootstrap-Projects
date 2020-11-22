/*----------------------------------------
File Name: PlanesObject.h
Purpose: Handles physics as if
it was a plane
Author: Tarn Cooper
Modified: 13/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "SceneObject.h"
//A class that inherits from sceneObject to control physics of the a plane
class PlanesObject : public SceneObject
{
public:
//-----------------------------------------------------------
// Constructs Plane object
// x(float): How much in x direction is it facing?
// y(float): How much in y direction is it facing?
// inD (float): How far in opposite direction of normal should
//				this plane move from center?
//-----------------------------------------------------------
	PlanesObject(float x, float y, float inD);
//-----------------------------------------------------------
// Destroys Circle object
//-----------------------------------------------------------
	virtual ~PlanesObject() {};

//-----------------------------------------------------------
// Function for getting distance between this plane and a 
// point. This is also used to get which side of plane it is.
// p (const Vec2<float>): Where is other point?
// return (float): Returns distance in positive or negative
//				   depending on which side of plane.
//-----------------------------------------------------------
	float distanceTo(const Vec2<float> p);

//-----------------------------------------------------------
// Gets distance from world this plane has moved
// return (float): Returns distance moved.
//-----------------------------------------------------------
	float getDistance();
//-----------------------------------------------------------
// virtual function Gets closest point to other point
// p (const Vec2<float>&): What is other point?
// return (Vec2<float>): Returns the closest point.
//-----------------------------------------------------------
	virtual Vec2<float> closestPoint(const Vec2<float>& p) override;
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

	//Basic enum for detemining where the point is to plane
	enum ePlaneResult
	{
		FRONT = 1,
		BACK = -1,
		INTERSECTS = 0
	};
//-----------------------------------------------------------
// Tests where a scene object is to the plane
// p (const Vec2<float>): Where is other point?
// return (ePlaneResult): Returns which side point is to plane
//-----------------------------------------------------------
	ePlaneResult testSide(const Vec2<float>& p);

protected:
	float distance = 0; //Holds distance from world center position

};

