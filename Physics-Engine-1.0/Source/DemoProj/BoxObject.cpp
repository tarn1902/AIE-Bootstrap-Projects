/*----------------------------------------
File Name: BoxObject.cpp
Purpose: Holds sall function for 
		 BoxObject.h
Author: Tarn Cooper
Modified: 14/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/

#include "BoxObject.h"
#include "RayObject.h"
#include "PlanesObject.h"
#include "CircleObject.h"
#include "Texture.h"
#include "Utilities.h"
#include <math.h>

//-----------------------------------------------------------
// Constructs Box object
// inTexture(aie::Texture*): What texture to use?
// inSpeed (float): How fast is this moving?
//-----------------------------------------------------------
BoxObject::BoxObject(aie::Texture* inTexture, float inSpeed)
{
	speed = inSpeed;
	m_texture = inTexture;
	direction = { m_localTransform.yAxis.x, m_localTransform.yAxis.y };
	rayRange = (float)std::sqrt(m_texture->getHeight() * m_texture->getHeight() + m_texture->getWidth() * m_texture->getWidth()) * 2;
	m_texture->getFilename().c_str();

}

//-----------------------------------------------------------
// Gets vector of maximum point of object
// returns(Vec2<float>): Returns maximum of box point
//-----------------------------------------------------------
Vec2<float> BoxObject::getMaxPoint()
{
	return m_max;
}

//-----------------------------------------------------------
// Gets vector of minmum point of object
// returns(Vec2<float>): Returns minimum of box point
//-----------------------------------------------------------
Vec2<float> BoxObject::getMinPoint()
{
	return m_min;
}

//-----------------------------------------------------------
// Virtual function for drawing on renderer
// renderer (aie::Renderer2D*): What renderer will it draw 
//								on?
//-----------------------------------------------------------
void BoxObject::onDraw(aie::Renderer2D* renderer)
{
	renderer->drawSpriteTransformed3x3(m_texture, (float*)&m_globalTransform);
}

//-----------------------------------------------------------
// Gets vector of forward direction
// returns(Vec2<float>): Returns forward direction of object
//-----------------------------------------------------------
Vec2<float> BoxObject::getForwardDirection()
{
	return { getLocalTransform().yAxis.x, getLocalTransform().yAxis.y };
}

//-----------------------------------------------------------
// Virtual function for updating the objects transformation
// deltaTime (float): How long since last update?
//-----------------------------------------------------------    
void BoxObject::onUpdate(float deltaTime)
{
	//Basic matrix updates
	translate(direction.x * speed * deltaTime, direction.y * speed * deltaTime);
	rotate(rotation);
	m_min = Vec2<float>(getGlobalTransform().zAxis.x - m_texture->getWidth() / 2, getGlobalTransform().zAxis.y - m_texture->getHeight() / 2);
	m_max = Vec2<float>(getGlobalTransform().zAxis.x + m_texture->getWidth()/2, getGlobalTransform().zAxis.y + m_texture->getHeight()/2);

	for (auto child : m_parent->getChildren())
	{
		if (CheckCollision(child) && child != this && child != getParent()->getChild(0))
		{	
			Vec2<float> intersection;
			Vec2<float> reflection;

			CircleObject* otherCircle = dynamic_cast<CircleObject*>(child);
			
			if (otherCircle != nullptr) //Testing if scene object is a circle object
			{
				if (RayObject(otherCircle->Center(), otherCircle->getDirection(), otherCircle->getRayRange()).intersectSlide(this, &intersection, &reflection))
				{
					//Testing for nan for reflection because may return nan for 0, 0 reflection vector
 					if (!isnan(reflection.normalised().x))
					{
						reflection.normalise();
					}
  					otherCircle->setDirection({ reflection.x , reflection.y  });
				}
				else if (RayObject({otherCircle->Center().x + otherCircle->getRadius() * cosf(0), otherCircle->Center().y + otherCircle->getRadius() * sinf(0) }, otherCircle->getDirection(), otherCircle->getRayRange()).intersectSlide(this, &intersection, &reflection))
				{
					//Testing for nan for reflection because may return nan for 0, 0 reflection vector
					if (!isnan(reflection.normalised().x))
					{
						reflection.normalise();
					}
					otherCircle->setDirection({ reflection.x , reflection.y });
				}
				else if (RayObject({ otherCircle->Center().x + otherCircle->getRadius() * cosf(180), otherCircle->Center().y + otherCircle->getRadius() * sinf(180) }, otherCircle->getDirection(), otherCircle->getRayRange()).intersectSlide(this, &intersection, &reflection))
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
	}
	for (auto child : this->getChildren())
	{
		child->onUpdate(deltaTime);
	}
}

//-----------------------------------------------------------
// Gets center of object as a point
// return (Vec2<float>): Returns point in center.						  
//-----------------------------------------------------------
Vec2<float> BoxObject::Center() const {
	return (m_min + m_max) * 0.5f;
}

//-----------------------------------------------------------
// Virtual function for checking if collision occured
// other (SceneObject*): What is other object?
// return (bool): Returns true if collsion occured
//-----------------------------------------------------------
bool BoxObject::CheckCollision(SceneObject* other) {
	
	BoxObject* otherBox = dynamic_cast<BoxObject*>(other);
	if (otherBox != nullptr)//Testing if scene object is a box object
	{
		return !(m_max.x < otherBox->m_min.x || m_max.y < otherBox->m_min.y ||
			m_min.x > otherBox->m_max.x || m_min.y > otherBox->m_max.y);
	}

	CircleObject* otherCircle = dynamic_cast<CircleObject*>(other);
	if (otherCircle != nullptr)//Testing if scene object is a circle object
	{
		auto diff = closestPoint(otherCircle->Center()) - otherCircle->Center();
		return diff.dot(diff) <= (otherCircle->getRadius() * otherCircle->getRadius());
	}
	return false;
}

//-----------------------------------------------------------
// virtual function Gets closest point to other point
// point (const Vec2<float>&): What is other point?
// return (Vec2<float>): Returns the closest point.
//-----------------------------------------------------------
Vec2<float> BoxObject::closestPoint(const Vec2<float>& p) {
	return clamp(p, m_min, m_max);
}

//-----------------------------------------------------------
// Gets vector of each corner on object
// return (std::vector<Vec2<float>>): Returns all corners in 
//									  list point.							  
//-----------------------------------------------------------
std::vector<Vec2<float>> BoxObject::getCorners() const {
	std::vector<Vec2<float>> corners(4);
	corners[0] = Vec2<float>(getGlobalTransform().zAxis.x - m_texture->getWidth() / 2, getGlobalTransform().zAxis.y - m_texture->getHeight() / 2);
	corners[1] = { getGlobalTransform().zAxis.x - m_texture->getWidth() / 2, getGlobalTransform().zAxis.y + m_texture->getHeight() / 2 };
	corners[2] = Vec2<float>(getGlobalTransform().zAxis.x + m_texture->getWidth() / 2, getGlobalTransform().zAxis.y + m_texture->getHeight() / 2);
	corners[3] = { getGlobalTransform().zAxis.x + m_texture->getWidth() / 2, getGlobalTransform().zAxis.y - m_texture->getHeight() / 2 };
	return corners;
}

