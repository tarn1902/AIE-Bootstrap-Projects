/*----------------------------------------
File Name: Plane.cpp
Purpose: Acts as a plane in physics scene
Author: Tarn Cooper
Modified: 10 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Plane.h"
#include<Gizmos.h>

//-----------------------------------------------------------
// Constructs Plane
// inNormal (glm::vec2): What is the nomral of plane?
// inDistance (float): What is the distance of plane for center?
//-----------------------------------------------------------
Plane::Plane(glm::vec2 inNormal, float inDistance) : PhysicsObject(PLANE)
{
	normal = inNormal;
	distanceToOrigin = inDistance;
}

//-----------------------------------------------------------
// Destructs Plane
//-----------------------------------------------------------
Plane::~Plane()
{

}

//-----------------------------------------------------------
// Updates each fixed update
// inGravity (glm::vec2): What is the gravity on this object?
// inTimeStep (glm::vec2): What is the current time step?
//-----------------------------------------------------------
void Plane::FixedUpdate(glm::vec2 inGravity, float inTimeStep)
{

}

//-----------------------------------------------------------
// Able to debug each update
//-----------------------------------------------------------
void Plane::Debug()
{

}

//-----------------------------------------------------------
// Creates visuals of object
//-----------------------------------------------------------
void Plane::MakeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = normal * distanceToOrigin;
	// easy to rotate normal through 90 degrees around z
	glm::vec2 parallel(normal.y, -normal.x);
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, colour);
}

//-----------------------------------------------------------
// Gets normal of object
//	return (glm::vec2): returns normal of plane
//-----------------------------------------------------------
glm::vec2 Plane::GetNormal()
{ 
	return normal; 
}

//-----------------------------------------------------------
// Gets distance of object from center
//	return (float): returns distance of plane from center
//-----------------------------------------------------------
float Plane::GetDistance()
{ 
	return distanceToOrigin;
}