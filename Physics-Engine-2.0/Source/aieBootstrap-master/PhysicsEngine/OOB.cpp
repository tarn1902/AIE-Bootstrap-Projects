/*----------------------------------------
File Name: OOB.cpp
Purpose: Acts as a OOB in physics scene
Author: Tarn Cooper
Modified: 06 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "OOB.h"
#include <Gizmos.h>

//-----------------------------------------------------------
// Constructs OOB
//	inPosition (glm::vec2) : What position is OOB in?
//	inVelocity (glm::vec2) : What velocity is OOB at?
//	inMass (float) : What is mass of OOB?
//  inExtents(glm::vec2) : What are extents of OOB?
//  inColour(glm::vec4) : What colour is the OOB?
//-----------------------------------------------------------
OOB::OOB(glm::vec2 inPosition, glm::vec2 inVelocity, float inMass, glm::vec2 inExtents, glm::vec4 inColour) : Rigidbody(BOX, inPosition, inVelocity, 0, inMass)
{
	colour = inColour;
	extents = inExtents;
	moment = 1.0f / 12.0f * mass * extents.x * 2 * extents.y * 2;
}

//-----------------------------------------------------------
// Destructs OOB
//-----------------------------------------------------------
OOB::~OOB()
{

}

//-----------------------------------------------------------
// Sets rotation of oob on top of rigidbodys fixed update
// inGravity (glm::vec2): How much gravity is acting upon object?
// inTimestep (float): What is the current time step?
//-----------------------------------------------------------
void OOB::FixedUpdate(glm::vec2 inGravity, float inTimeStep)
{
	Rigidbody::FixedUpdate(inGravity, inTimeStep);

	float cs = cosf(rotation);
	float sn = sinf(rotation);

	localX = glm::normalize(glm::vec2(cs, sn));
	localY = glm::normalize(glm::vec2(-sn, cs));
}

//-----------------------------------------------------------
// Creates visuals of object
//-----------------------------------------------------------
void OOB::MakeGizmo()
{
	glm::vec2 p1 = position - localX * extents.x - localY * extents.y;
	glm::vec2 p2 = position + localX * extents.x - localY * extents.y;
	glm::vec2 p3 = position - localX * extents.x + localY * extents.y;
	glm::vec2 p4 = position + localX * extents.x + localY * extents.y;
	aie::Gizmos::add2DTri(p1, p2, p4, colour);
	aie::Gizmos::add2DTri(p1, p4, p3, colour);

}

//-----------------------------------------------------------
// Get width of object
// return (float): Returns the width of object
//-----------------------------------------------------------
float OOB::GetWidth()
{
	return extents.x * 2;
}

//-----------------------------------------------------------
// Get height of object
// return (float): Returns the height of object
//-----------------------------------------------------------
float OOB::GetHeight()
{
	return extents.y * 2;
}

//-----------------------------------------------------------
// Get extents of object
// return (glm::vec2): Returns the extents of object
//-----------------------------------------------------------
glm::vec2 OOB::GetExtents()
{
	return extents;
}

//-----------------------------------------------------------
// Get local X of object
// return (glm::vec2): Returns the local X of object
//-----------------------------------------------------------
glm::vec2 OOB::GetLocalX()
{
	return localX;
}

//-----------------------------------------------------------
// Get local Y of object
// return (glm::vec2): Returns the local Y of object
//-----------------------------------------------------------
glm::vec2 OOB::GetLocalY()
{
	return localY;
}

//-----------------------------------------------------------
// Get center of object
// return (glm::vec2): Returns the center of object
//-----------------------------------------------------------
glm::vec2 OOB::GetCenter()
{
	return position;
}

//-----------------------------------------------------------
// Checks collision of two boxes
//	inBox (OOB&) : What is other box?
//	inContact (glm::vec2) : What is current contact point?
//	inNumContacts (int&) : How many times has contact happened?
//  inPen(float&) : What is current penetration length?
//  inEdgeNormal(glm::vec2) : What is current edge normal?
//	return (bool): Returns true if boxes intersect
//-----------------------------------------------------------
bool OOB::CheckBoxCorners(OOB& inBox, glm::vec2& inContact, int& inNumContacts, float& inPen, glm::vec2& inEdgeNormal)
{
	float minX, maxX, minY, maxY;
	float boxW = inBox.GetExtents().x * 2;
	float boxH = inBox.GetExtents().y * 2;
	int numLocalContacts = 0;
	glm::vec2 localContact(0, 0);
	bool first = true;

	//Checks if collision has happened
	for (float x = -inBox.GetExtents().x; x < boxW; x += boxW)
	{
		for (float y = -inBox.GetExtents().y; y < boxH; y += boxH)
		{
			glm::vec2 p = inBox.GetCenter() + x * inBox.localX + y * inBox.localY;
			glm::vec2 p0(glm::dot(p - position, localX), glm::dot(p - position, localY));
			if (first || p0.x < minX)
			{
				minX = p0.x;
			}
			if (first || p0.x > maxX)
			{
				maxX = p0.x;
			}
			if (first || p0.y < minY)
			{
				minY = p0.y;
			}
			if (first || p0.y > maxY)
			{
				maxY = p0.y;
			}
			if (p0.x >= -extents.x && p0.x <= extents.x && p0.y >= -extents.y && p0.y <= extents.y)
			{
				numLocalContacts++;
				localContact += p0;
			}
			first = false;
		}
	}

	if (maxX <-extents.x || minX >extents.x || maxY<-extents.y || minY >extents.y)
	{
		return false;
	}
		
	if (numLocalContacts == 0)
	{
		return false;
	}
		
	bool res = false;
	inContact += position + (localContact.x * localX + localContact.y * localY) / (float)numLocalContacts;
	inNumContacts++;

	//Checks penetration length
	float pen0 = extents.x - minX;
	if (pen0 > 0 && (pen0 < inPen || inPen == 0)) {
		inEdgeNormal = localX;
		inPen = pen0;
		res = true;
	}

	pen0 = maxX + extents.x;
	if (pen0 > 0 && (pen0 < inPen || inPen == 0)) {
		inEdgeNormal = -localX;
		inPen = pen0;
		res = true;
	}

	pen0 = extents.y - minY;
	if (pen0 > 0 && (pen0 < inPen || inPen == 0)) {
		inEdgeNormal = localY;
		inPen = pen0;
		res = true;
	}

	pen0 = maxY + extents.y;
	if (pen0 > 0 && (pen0 < inPen || inPen == 0)) {
		inEdgeNormal = -localY;
		inPen = pen0;
		res = true;
	}

	return res;
}

