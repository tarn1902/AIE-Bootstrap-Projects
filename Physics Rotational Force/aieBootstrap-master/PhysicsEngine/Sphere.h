#pragma once
#include "Rigidbody.h"
class Sphere : public Rigidbody
{
public:
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);
	~Sphere();
	virtual void MakeGizmo();
	virtual bool CheckCollision(PhysicsObject* pOther);
	float GetRadius();
	glm::vec4 GetColour();
protected:
	float radius;
	glm::vec4 colour;
};

