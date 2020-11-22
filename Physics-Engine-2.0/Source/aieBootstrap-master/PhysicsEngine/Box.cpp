/*----------------------------------------
File Name: Box.cpp
Purpose: Acts as a box in physics scene
Author: Tarn Cooper
Modified: 05 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Box.h"
#include <Gizmos.h>
//-----------------------------------------------------------
// Constructs Box
//	inPosition (glm::vec2) : What position is box in?
//	inVelocity (glm::vec2) : What velocity is box at?
//	inMass (float) : What is mass of box?
//  inExtents(glm::vec2) : What are extents of box?
//  inColour(glm::vec4) : What colour is the box?
//-----------------------------------------------------------
Box::Box(glm::vec2 inPosition, glm::vec2 inVelocity, float inMass, glm::vec2 inExtents, glm::vec4 inColour) : Rigidbody(BOX, inPosition, inVelocity, 0, inMass)
{
	colour = inColour;
	extents = inExtents;
}
//-----------------------------------------------------------
// Destructs Box
//-----------------------------------------------------------
Box::~Box()
{

}

//-----------------------------------------------------------
// Creates visuals of object
//-----------------------------------------------------------
void Box::MakeGizmo()
{
	aie::Gizmos::add2DAABBFilled(position, extents, colour);
}

//-----------------------------------------------------------
// Get the extents of object
// return (glm::vec2): Returns the extent of object
//-----------------------------------------------------------
glm::vec2 Box::GetExtents()
{
	return extents;
}

