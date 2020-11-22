/*----------------------------------------
File Name: RayObject.h
Purpose: Holds all function for
		 rayObject.h
Author: Tarn Cooper
Modified: 13/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "RayObject.h"
#include "BoxObject.h"
#include "CircleObject.h"
#include "PlanesObject.h"
#include "Utilities.h"
#include <math.h>
//-----------------------------------------------------------
// Constructs ray object
// start (const Vec2<float>&): What point does it start?
// dir (const Vec2<float>&): What direction does it travel?
// l (float): How far will it travel? *default INFINITY*
//-----------------------------------------------------------
RayObject::RayObject(const Vec2<float>& start, const Vec2<float>& dir, float l)
{
	origin = start;
	direction = dir;
	length = l;
}
//-----------------------------------------------------------
// virtual function Gets closest point to other point
// point (const Vec2<float>&): What is other point?
// return (Vec2<float>): Returns the closest point.
//-----------------------------------------------------------
Vec2<float> RayObject::closestPoint(const Vec2<float>& point)
{
	// ray origin to arbitrary point
	auto p = point - origin;
	// project the point onto the ray and clamp by length
	float t = clamp(p.dot(direction), 0, length);
	// return position in direction of ray
	return origin + direction * t;
}
//-----------------------------------------------------------
// Function for testing if intersects with object. Will also
// find reflection and point of intersection.
// other (SceneObject*): What other object could it collide 
//	with?
// I (Vec2<float>*): Returns intersection if pointer is put 
//					 in *defaults to nullptr*
// S (Vec2<float>*): Returns reflection if pointer is put 
//					 in *defaults to nullptr*
// return (bool): Returns if intersection occured. Will also
//-----------------------------------------------------------
bool RayObject::intersectBounce(SceneObject* other, Vec2<float>* I, Vec2<float>* S) const
{
	CircleObject* otherCircle = dynamic_cast<CircleObject*>(other);
	if (otherCircle != nullptr) //Testing if scene object is a circle object
	{
		// ray origin to sphere Center()
		auto L = otherCircle->Center() - origin;

		// project sphere Center() onto ray
		float t = L.dot(direction);

		// get sqr distance from sphere Center() to ray
		float dd = L.dot(L) - t * t;

		// subtract penetration amount from projected distance
		t -= sqrt(otherCircle->getRadius() * otherCircle->getRadius() - dd);

		// it intersects if within ray length
		if (t >= 0 && t <= length) {
			// store intersection point if requested
			if (I != nullptr)
				*I = origin + direction * t;
			if (S != nullptr) {
				// get surface normal at intersection point
				auto N = ((origin + direction * t) - otherCircle->Center());
				N /= otherCircle->getRadius();
				// get penetration vector
				auto P = direction * (length - t);
				// get penetration amount
				float p = P.dot(N);
				// get reflected vector
				*S = N * -2 * p + P; //bounce
				
			}
			return true;
		}
		// default no intersection
		return false;
	}

	PlanesObject* otherPlanes = dynamic_cast<PlanesObject*>(other);
	if (otherPlanes != nullptr)//Testing if scene object is a planes object
	{
		// project ray direction onto plane normal
		// this should give us a value between -1 and 1
		float t = direction.dot(otherPlanes->getDirection());
		// must face the plane
		if (t > 0)
			return false;
		// get distance of ray origin to the plane
		float d = origin.dot(otherPlanes->getDirection()) + otherPlanes->getDistance();
		// check if ray is parallel with the plane
		// no intersection if parallel and not touching
		if (t == 0 && d != 0)
			return false;
		// calculate distance along ray to plane
		t = d == 0 ? 0 : -(d / t);
		// intersects if within range
		if (t >= 0 &&
			t <= length) {
			// store intersection point if requested
			if (I != nullptr)
				*I = origin + direction * t;
			if (S != nullptr) {
				// get penetration vector
				auto P = direction * (length - t);
				// get penetration amount
				float p = P.dot(otherPlanes->getDirection());
				// get reflected vector
					*S = otherPlanes->getDirection() * -2 * p + P; //bounce

				
			}

			return true;
		}
		// default no intersection
		return false;
	}
	BoxObject* otherBox = dynamic_cast<BoxObject*>(other);
	if (otherBox != nullptr)//Testing if scene object is a box object
	{
		float xmin, xmax, ymin, ymax;

		// get min and max in the x-axis
		if (direction.x < 0) {
			xmin = (otherBox->getMaxPoint().x - origin.x) / direction.x;
			xmax = (otherBox->getMinPoint().x - origin.x) / direction.x;
		}
		else {
			xmin = (otherBox->getMinPoint().x - origin.x) / direction.x;
			xmax = (otherBox->getMaxPoint().x - origin.x) / direction.x;
		}
		// get min and max in the y-axis
		if (direction.y < 0) {
			ymin = (otherBox->getMaxPoint().y - origin.y) / direction.y;
			ymax = (otherBox->getMinPoint().y - origin.y) / direction.y;
		}
		else {
			ymin = (otherBox->getMinPoint().y - origin.y) / direction.y;
			ymax = (otherBox->getMaxPoint().y - origin.y) / direction.y;
		}

		// ensure within box
		if (xmin > ymax || ymin > xmax)
			return false;
		// the first contact is the largest of the two min
		float t = max(xmin, ymin);
		// intersects if within range
		if (t >= 0 && t <= length) {
			// store intersection point if requested
			if (I != nullptr)
				*I = origin + direction * t;
			if (S != nullptr) {
				// need to determine box side hit
				Vec2<float> N = {};
				if (t == xmin) {
					// horizontal normal
					if (direction.x < 0)
						// right side
						N = { 1,0 };
					else
						// left side
						N = { -1,0 };
				}
				else {
					// vertical normal
					if (direction.y < 0)
						// top
						N = { 0,1 };
					else
						// bottom
						N = { 0,-1 };
				}
				// get penetration vector
				auto P = direction * (length - t);
				// get penetration amount
				float p = P.dot(N);
				// get reflected vector
					*S = N * -2 * p + P; //bounce
				
			}
			return true;
		}
		// more to come here...
		// not within Ray's range
		return false;
	}
	return false;
}

//-----------------------------------------------------------
// Function for testing if intersects with object. Will also
// find reflection and point of intersection.
// other (SceneObject*): What other object could it collide 
//	with?
// I (Vec2<float>*): Returns intersection if pointer is put 
//					 in *defaults to nullptr*
// S (Vec2<float>*): Returns slide direction if pointer is 
//					 put in *defaults to nullptr*
// return (bool): Returns if intersection occured. Will also
//-----------------------------------------------------------
bool RayObject::intersectSlide(SceneObject* other, Vec2<float>* I, Vec2<float>* S) const
{
	CircleObject* otherCircle = dynamic_cast<CircleObject*>(other);
	if (otherCircle != nullptr)//Testing if scene object is a circle object
	{
		// ray origin to sphere Center()
		auto L = otherCircle->Center() - origin;

		// project sphere Center() onto ray
		float t = L.dot(direction);

		// get sqr distance from sphere Center() to ray
		float dd = L.dot(L) - t * t;

		// subtract penetration amount from projected distance
		t -= sqrt(otherCircle->getRadius() * otherCircle->getRadius() - dd);

		// it intersects if within ray length
		if (t >= 0 && t <= length) {
			// store intersection point if requested
			if (I != nullptr)
				*I = origin + direction * t;
			if (S != nullptr) {
				// get surface normal at intersection point
				auto N = ((origin + direction * t) - otherCircle->Center());
				N /= otherCircle->getRadius();
				// get penetration vector
				auto P = direction * (length - t);
				// get penetration amount
				float p = P.dot(N);
				// get reflected vector
				
				*S = N * -1 * p + P; //slide

			}
			return true;
		}
		// default no intersection
		return false;
	}

	PlanesObject* otherPlanes = dynamic_cast<PlanesObject*>(other);
	if (otherPlanes != nullptr)//Testing if scene object is a planes object
	{
		// project ray direction onto plane normal
		// this should give us a value between -1 and 1
		float t = direction.dot(otherPlanes->getDirection());
		// must face the plane
		if (t > 0)
			return false;
		// get distance of ray origin to the plane
		float d = origin.dot(otherPlanes->getDirection()) + otherPlanes->getDistance();
		// check if ray is parallel with the plane
		// no intersection if parallel and not touching
		if (t == 0 && d != 0)
			return false;
		// calculate distance along ray to plane
		t = d == 0 ? 0 : -(d / t);
		// intersects if within range
		if (t >= 0 &&
			t <= length) {
			// store intersection point if requested
			if (I != nullptr)
				*I = origin + direction * t;
			if (S != nullptr) {
				// get penetration vector
				auto P = direction * (length - t);
				// get penetration amount
				float p = P.dot(otherPlanes->getDirection());
				// get reflected vector

				*S = otherPlanes->getDirection()  * -1 * p + P; //slide

			}

			return true;
		}
		// default no intersection
		return false;
	}
	BoxObject* otherBox = dynamic_cast<BoxObject*>(other);
	if (otherBox != nullptr)//Testing if scene object is a box object
	{
		float xmin, xmax, ymin, ymax;

		// get min and max in the x-axis
		if (direction.x < 0) {
			xmin = (otherBox->getMaxPoint().x - origin.x) / direction.x;
			xmax = (otherBox->getMinPoint().x - origin.x) / direction.x;
		}
		else {
			xmin = (otherBox->getMinPoint().x - origin.x) / direction.x;
			xmax = (otherBox->getMaxPoint().x - origin.x) / direction.x;
		}
		// get min and max in the y-axis
		if (direction.y < 0) {
			ymin = (otherBox->getMaxPoint().y - origin.y) / direction.y;
			ymax = (otherBox->getMinPoint().y - origin.y) / direction.y;
		}
		else {
			ymin = (otherBox->getMinPoint().y - origin.y) / direction.y;
			ymax = (otherBox->getMaxPoint().y - origin.y) / direction.y;
		}

		// ensure within box
		if (xmin > ymax || ymin > xmax)
			return false;
		// the first contact is the largest of the two min
		float t = max(xmin, ymin);
		// intersects if within range
		if (t >= 0 && t <= length) {
			// store intersection point if requested
			if (I != nullptr)
				*I = origin + direction * t;
			if (S != nullptr) {
				// need to determine box side hit
				Vec2<float> N = {};
				if (t == xmin) {
					// horizontal normal
					if (direction.x < 0)
						// right side
						N = { 1,0 };
					else
						// left side
						N = { -1,0 };
				}
				else {
					// vertical normal
					if (direction.y < 0)
						// top
						N = { 0,1 };
					else
						// bottom
						N = { 0,-1 };
				}
				// get penetration vector
				auto P = direction * (length - t);
				// get penetration amount
				float p = P.dot(N);
				// get reflected vector
				*S = N * -1 * p + P; //slide

			}
			return true;
		}
		return false;
	}
	return false;
}



