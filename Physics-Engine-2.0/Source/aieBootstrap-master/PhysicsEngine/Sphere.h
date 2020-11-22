/*----------------------------------------
File Name: Sphere.h
Purpose:  Acts as a sphere in physics scene
Author: Tarn Cooper
Modified: 08 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Rigidbody.h"
class Sphere : public Rigidbody
{
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);
	~Sphere();
	virtual void MakeGizmo();
	float GetRadius();
protected:
	float radius;
};

