/*----------------------------------------
File Name: PlanesObject.cpp
Purpose: Holds all function for
		 planesObject.h
Author: Tarn Cooper
Modified: 15/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "PlanesObject.h"
#include "BoxObject.h"
#include "CircleObject.h"
#include "RayObject.h"
using namespace std;
//-----------------------------------------------------------
// Constructs Plane object
// x(float): How much in x direction is it facing?
// y(float): How much in y direction is it facing?
// inD (float): How far in opposite direction of normal should
//				this plane move from center?
//-----------------------------------------------------------
PlanesObject::PlanesObject(float x, float y, float inD)
{
	direction = Vec2<float>(x, y);
	distance = inD;
}
//-----------------------------------------------------------
// Function for getting distance between this plane and a 
// point. This is also used to get which side of plane it is.
// p (const Vec2<float>): Where is other point?
// return (float): Returns distance in positive or negative
//				   depending on which side of plane.
//-----------------------------------------------------------
float PlanesObject::distanceTo(const Vec2<float> p)
{
	return p.dot(getDirection()) + distance;
}
//-----------------------------------------------------------
// virtual function Gets closest point to other point
// p (const Vec2<float>&): What is other point?
// return (Vec2<float>): Returns the closest point.
//-----------------------------------------------------------
Vec2<float> PlanesObject::closestPoint(const Vec2<float>& p)  
{
	return p - getDirection() * distanceTo(p);
}
//-----------------------------------------------------------
// Virtual function for updating the objects transformation
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
void PlanesObject::onUpdate(float deltaTime)
{

	for (auto child : m_parent->getChildren())
	{
		if (CheckCollision(child) == PlanesObject::ePlaneResult::INTERSECTS && child != this && dynamic_cast<PlanesObject*>(child) == nullptr)
		{
			Vec2<float> intersection;
			Vec2<float> reflection;
			CircleObject* otherCircle = dynamic_cast<CircleObject*>(child);
			if (otherCircle != nullptr)//Testing if scene object is a circle object
			{
				if (RayObject(otherCircle->Center(), otherCircle->getDirection(), otherCircle->getRayRange()).intersectBounce(this, &intersection, &reflection))
				{
					//Testing for nan for reflection because may return nan for 0, 0 reflection vector
					if (!isnan(reflection.normalised().x))
					{
						reflection.normalise();
					}
					otherCircle->setDirection(Vec2<float>(reflection.x, reflection.y));
				}
				else if (RayObject({ otherCircle->Center().x + otherCircle->getRadius() * cosf(0), otherCircle->Center().y + otherCircle->getRadius() * sinf(0) }, otherCircle->getDirection(), otherCircle->getRayRange()).intersectBounce(this, &intersection, &reflection))
				{
					//Testing for nan for reflection because may return nan for 0, 0 reflection vector
					if (!isnan(reflection.normalised().x))
					{
						reflection.normalise();
					}
					otherCircle->setDirection({ reflection.x , reflection.y });
				}
				else if (RayObject({ otherCircle->Center().x + otherCircle->getRadius() * cosf(180), otherCircle->Center().y + otherCircle->getRadius() * sinf(180) }, otherCircle->getDirection(), otherCircle->getRayRange()).intersectBounce(this, &intersection, &reflection))
				{
					//Testing for nan for reflection because may return nan for 0, 0 reflection vector
					if (!isnan(reflection.normalised().x))
					{
						reflection.normalise();
					}
					otherCircle->setDirection({ reflection.x , reflection.y });
				}
				//otherCircle->translate(getDirection().x * otherCircle->getSpeed() / 2 * deltaTime, getDirection().y * otherCircle->getSpeed() / 2 * deltaTime);
			}
			

			BoxObject* otherBox = dynamic_cast<BoxObject*>(child);

			if (otherBox != nullptr)//Testing if scene object is a box object
			{
				
				if (RayObject(otherBox->Center(), otherBox->getDirection(), otherBox->getRayRange()).intersectSlide(this, &intersection, &reflection))
				{
					//Testing for nan for reflection because may return nan for 0, 0 reflection vector
					if (!isnan(reflection.normalised().x))
					{
						reflection.normalise();
					}
					otherBox->setDirection({ reflection.x , reflection.y });
				}
				otherBox->translate(getDirection().x * otherBox->getSpeed() / 2 * deltaTime, getDirection().y* otherBox->getSpeed() / 2 * deltaTime);
			}

			
		}
	}
}
//-----------------------------------------------------------
// Tests where a scene object is to the plane
// p (const Vec2<float>): Where is other point?
// return (ePlaneResult): Returns which side point is to plane
//-----------------------------------------------------------
PlanesObject::ePlaneResult PlanesObject::testSide(const Vec2<float>& p)
{
	float t = distanceTo(p);
	if (t < 0)
		return PlanesObject::ePlaneResult::BACK;
	else if (t > 0)
		return PlanesObject::ePlaneResult::FRONT;
	return PlanesObject::ePlaneResult::INTERSECTS;
}
//-----------------------------------------------------------
// Gets distance from world this plane has moved
// return (float): Returns distance moved.
//-----------------------------------------------------------
float PlanesObject::getDistance()
{
	return distance;
}

//-----------------------------------------------------------
// Virtual function for checking if collision occured
// other (SceneObject*): What is other object?
// return (bool): Returns true if collsion occured
//-----------------------------------------------------------
bool PlanesObject::CheckCollision(SceneObject* other) 
{
	CircleObject* otherCircle = dynamic_cast<CircleObject*>(other);
	if (otherCircle != nullptr)//Testing if scene object is a circle object
	{
		float t = distanceTo(otherCircle->Center());
		if (t > otherCircle->getRadius())
			return true;
		else if (t < -otherCircle->getRadius())
			return true;
		return false;
	}

	BoxObject* otherBox = dynamic_cast<BoxObject*>(other);
	if (otherBox != nullptr) //Testing if scene object is a box object
	{
		// tag if we find a corner on each side
		bool side[2] = { false, false };
		// compare each corner
		for (auto c : otherBox->getCorners()) {
		
			auto result = testSide(c);
			if (result == ePlaneResult::FRONT)
				side[0] = true;
			else if (result == ePlaneResult::BACK)
				side[1] = true;
		}
		// if front but not back
		if (side[0] && !side[1])
			return true;
		// if back but not front
		else if (!side[0] && side[1])
			return true;
		// else overlapping
		return false;
	}
	return true;
}


