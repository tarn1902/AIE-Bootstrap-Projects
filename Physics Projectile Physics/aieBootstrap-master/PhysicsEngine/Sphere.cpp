/*----------------------------------------
File Name: Sphere.cpp
Purpose:  Acts as a sphere in physics scene
Author: Tarn Cooper
Modified: 10 March 2020
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
	aie::Gizmos::add2DCircle(position, radius, 10, colour);
}
//-----------------------------------------------------------
// Checks for collision between spheres
// inPOther (PhysicsObject*): What is the other object
// return (bool): Returns if collision occured
//-----------------------------------------------------------
bool Sphere::CheckCollision(PhysicsObject* inPOther)
{
	Sphere* pSphere = dynamic_cast<Sphere*>(inPOther);
	if (pSphere != nullptr)
	{
		if (glm::distance(position, pSphere->GetPosition()) < radius + pSphere->radius)
		{
			return true;
		}
	}
	return false;
}
//-----------------------------------------------------------
// Get radius of object
// return (float): Returns the radius of the object
//-----------------------------------------------------------
float Sphere::GetRadius() 
{ 
	return radius; 
}
//-----------------------------------------------------------
// Get colour of object
// return (glm::vec4): Returns the colour of the object
//-----------------------------------------------------------
glm::vec4 Sphere::GetColour() 
{ 
	return colour; 
}
