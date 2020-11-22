/*----------------------------------------
File Name: CircleObject.cpp
Purpose: Holds all function for
		 CircleObject.h
Author: Tarn Cooper
Modified: 14/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "CircleObject.h"
#include "BoxObject.h"
#include "RayObject.h"
#include "Utilities.h"
#include "Texture.h"

//-----------------------------------------------------------
// Constructs Circle object
// inTexture(aie::Texture*): What texture to use?
// inSpeed (float): how fast is this moving?
//-----------------------------------------------------------
CircleObject::CircleObject(aie::Texture* inTexture, float inSpeed)
{
	m_texture = inTexture;
	radius = (float)m_texture->getHeight() / 2;
	m_texture->getFilename();
	speed = inSpeed;
	direction = { m_localTransform.yAxis.x, m_localTransform.yAxis.y };
	rayRange = radius *2;
}
//-----------------------------------------------------------
// Virtual function for drawing on renderer
// renderer (aie::Renderer2D*): What renderer will it draw 
//								on?
//-----------------------------------------------------------
void CircleObject::onDraw(aie::Renderer2D* renderer)
{
	renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_globalTransform);
}

//-----------------------------------------------------------
// Gets radius of circle
// returns(float): Returns radius of circle
//----------------------------------------------------------
float CircleObject::getRadius()
{
	return radius;
}
//-----------------------------------------------------------
// Virtual function for updating the objects transformation
// deltaTime (float): How long since last update?
//-----------------------------------------------------------
void CircleObject::onUpdate(float deltaTime)
{
	translate(getDirection().x * speed * deltaTime, getDirection().y * speed * deltaTime);
	rotate(rotation);

	Center() = Vec2<float>(m_globalTransform.zAxis.x, m_globalTransform.zAxis.y);

	for (auto child : m_parent->getChildren())
	{
		if (CheckCollision(child) && child != this && child != getParent()->getChild(0))
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
					otherCircle->setDirection({ reflection.x , reflection.y  });
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
			}
			BoxObject* otherBox = dynamic_cast<BoxObject*>(child);
			
			if (otherBox != nullptr)//Testing if scene object is a box object
			{
				for (auto corner : otherBox->getCorners())
				{
					if (RayObject(corner, otherBox->getDirection(), otherBox->getRayRange()).intersectBounce(this, &intersection, &reflection))
					{
						//Testing for nan for reflection because may return nan for 0, 0 reflection vector
						if (!isnan(reflection.normalised().x))
						{
							reflection.normalise();
						}
						otherBox->setDirection({ reflection.x , reflection.y });
						break;
					}
				}
			}
		}

		for (auto child : this->getChildren())
		{
			child->onUpdate(deltaTime);
		}
	}
}

//-----------------------------------------------------------
// Virtual function for checking if collision occured
// other (SceneObject*): What is other object?
// return (bool): Returns true if collsion occured
//-----------------------------------------------------------
bool CircleObject::CheckCollision(SceneObject* other)
{
	CircleObject* otherCircle = dynamic_cast<CircleObject*>(other);
	if (otherCircle != nullptr) //Testing if scene object is a circle object
	{
		float r = radius + otherCircle->radius;
		Vec2<float> diff = otherCircle->Center() - Center();
		// compare distance between spheres to combined radii
		return diff.magnitudeSqr() <= (r * r);
	}

	BoxObject* otherBox = dynamic_cast<BoxObject*>(other);
	if (otherBox != nullptr) //Testing if scene object is a box object
	{
		auto diff = otherBox->closestPoint(Center()) - Center();
		return diff.dot(diff) <= (radius * radius);
	}
	return false;
}

//-----------------------------------------------------------
// Gets center of object as a point
// return (Vec2<float>): Returns point in center.						  
//-----------------------------------------------------------
Vec2<float> CircleObject::Center() const 
{
	return Vec2<float>(m_globalTransform.zAxis.x, m_globalTransform.zAxis.y);
}

//-----------------------------------------------------------
// virtual function Gets closest point to other point
// point (const Vec2<float>&): What is other point?
// return (Vec2<float>): Returns the closest point.
//-----------------------------------------------------------
Vec2<float> CircleObject::closestPoint(const Vec2<float>& p) {
	return Center();
}