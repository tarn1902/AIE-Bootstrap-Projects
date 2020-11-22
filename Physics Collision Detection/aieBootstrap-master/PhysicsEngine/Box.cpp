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
// Checks for collision between boxes
// inPOther (PhysicsObject*): What is the other object
// return (bool): Returns if collision occured
//-----------------------------------------------------------
bool Box::CheckCollision(PhysicsObject* inPOther)
{
	Box* pBox = dynamic_cast<Box*>(inPOther);
	if (pBox != nullptr)
	{
		if (position.x < pBox->GetPosition().x + pBox->GetExtents().x && 
			position.x + extents.x > pBox->GetPosition().x && 
			position.y < pBox->GetPosition().y + pBox->GetExtents().y && 
			position.y + extents.y > pBox->GetPosition().y) 
		{
			velocity = glm::vec2(0, 0);
			pBox->velocity = glm::vec2(0, 0);
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------
// Get the extents of object
// return (glm::vec2): Returns the extent of object
//-----------------------------------------------------------
glm::vec2 Box::GetExtents()
{
	return extents;
}

//-----------------------------------------------------------
// Get the colour of object
// return (glm::vec4): Returns the colour of object
//-----------------------------------------------------------
glm::vec4 Box::GetColour()
{
	return colour;
}
