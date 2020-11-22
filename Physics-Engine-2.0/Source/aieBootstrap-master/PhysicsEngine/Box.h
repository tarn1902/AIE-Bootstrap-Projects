/*----------------------------------------
File Name:Box.h
Purpose: Acts as a box in physics scene
Author: Tarn Cooper
Modified: 05 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Rigidbody.h"
class Box : public Rigidbody
{
public:
	Box(glm::vec2 inPosition, glm::vec2 inVelocity, float inMass, glm::vec2 inExtents, glm::vec4 inColour);
	~Box();
	virtual void MakeGizmo();
	glm::vec2  GetExtents();
protected:
	glm::vec2 extents;
};
