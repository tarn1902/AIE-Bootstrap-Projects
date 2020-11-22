/*----------------------------------------
File Name: RayObject.h
Purpose: Handles physics as if
it was a ray
Author: Tarn Cooper
Modified: 13/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "SceneObject.h"
//A class that inherits from sceneObject to control physics of the a ray
class RayObject : public SceneObject 
{
public:
//-----------------------------------------------------------
// Constructs ray object
// start (const Vec2<float>&): What point does it start?
// dir (const Vec2<float>&): What direction does it travel?
// l (float): How far will it travel? *default INFINITY*
//-----------------------------------------------------------
	RayObject(const Vec2<float>& start, const Vec2<float>& dir, float l = INFINITY);
//-----------------------------------------------------------
// Destroys Circle object
//-----------------------------------------------------------
	virtual ~RayObject() {};
//-----------------------------------------------------------
// virtual function Gets closest point to other point
// point (const Vec2<float>&): What is other point?
// return (Vec2<float>): Returns the closest point.
//-----------------------------------------------------------
	virtual Vec2<float> closestPoint(const Vec2<float>& point) override;
//-----------------------------------------------------------
// Function for testing if intersects with object. Will also
// find reflection and point of intersection.
// other (SceneObject*): What other object could it collide 
//	with?
// I (Vec2<float>*): Returns intersection if pointer is put 
//					 in *defaults to nullptr*
// S (Vec2<float>*): Returns reflection if pointer is put 
//					 in *defaults to nullptr*
// return (bool): Returns if intersection occured. Will also
//-----------------------------------------------------------
	bool intersectBounce(SceneObject* other, Vec2<float>* I = nullptr, Vec2<float>* S = nullptr) const;
//-----------------------------------------------------------
// Function for testing if intersects with object. Will also
// find reflection and point of intersection.
// other (SceneObject*): What other object could it collide 
//	with?
// I (Vec2<float>*): Returns intersection if pointer is put 
//					 in *defaults to nullptr*
// S (Vec2<float>*): Returns slide direction if pointer is 
//					 put in *defaults to nullptr*
// return (bool): Returns if intersection occured. Will also
//-----------------------------------------------------------
	bool intersectSlide(SceneObject* other, Vec2<float>* I = nullptr, Vec2<float>* S = nullptr) const;
protected:	Vec2<float> origin; //Holds orgin point of ray
	float length;		//Holds how far it will go
};

