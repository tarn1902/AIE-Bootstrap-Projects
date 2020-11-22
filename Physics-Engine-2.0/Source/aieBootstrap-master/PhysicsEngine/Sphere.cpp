/*----------------------------------------
File Name: Sphere.cpp
Purpose:  Acts as a sphere in physics scene
Author: Tarn Cooper
Modified: 08 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Sphere.h"
#include <Gizmos.h>
//-----------------------------------------------------------
// Construct Sphere
//	inPosition (glm::vec2): What position is object in?
//	inVelocity (glm::vec2): What velocity is object at?
//	inMass (float): What is the mass of object?
//	inRadius (float): What is radius of object?
//	inColour (glm::vec4) : what is the colour of object?
//-----------------------------------------------------------
Sphere::Sphere(glm::vec2 inPosition, glm::vec2 inVelocity, float inMass, float inRadius, glm::vec4 inColour) : Rigidbody(SPHERE, inPosition, inVelocity, 0, inMass)
{
	radius = inRadius;
	colour = inColour;
	moment =  0.5f * mass * radius * radius;
}
//-----------------------------------------------------------
// Destruct Sphere
//-----------------------------------------------------------
Sphere::~Sphere()
{

}

//-----------------------------------------------------------
// Creates visuals of object
//-----------------------------------------------------------
void Sphere::MakeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(rotation), std::sin(rotation)) *
		radius;
	aie::Gizmos::add2DCircle(position, radius, 12, colour);
	aie::Gizmos::add2DLine(position, position + end, glm::vec4(1, 1, 1, 1));
}

//-----------------------------------------------------------
// Get radius of object
// return (float): Returns the radius of the object
//-----------------------------------------------------------
float Sphere::GetRadius() 
{ 
	return radius; 
}

