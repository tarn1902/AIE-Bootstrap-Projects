/*----------------------------------------
File Name: OOB.h
Purpose: Acts as a OOB in physics scene
Author: Tarn Cooper
Modified: 06 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "Rigidbody.h"
class OOB : public Rigidbody
{
public:
	OOB(glm::vec2 inPosition, glm::vec2 inVelocity, float inMass, glm::vec2 inExtents, glm::vec4 inColour);
	~OOB();
	virtual void FixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void MakeGizmo();
	float GetWidth();
	float GetHeight();
	glm::vec2 GetExtents();
	glm::vec2 GetLocalX();
	glm::vec2 GetLocalY();
	glm::vec2 GetCenter();
	bool CheckBoxCorners(OOB& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal);

protected:
	glm::vec2 extents;
	glm::vec4 colour;
	glm::vec2 localX;
	glm::vec2 localY;
};

