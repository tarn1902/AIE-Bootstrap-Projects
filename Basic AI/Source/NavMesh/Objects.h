#pragma once
#include "..\MathsLibrarySLL\MathsLibrarySLL.h"
typedef Vec2<float> Vector2;
class Circle;
class Box;
class Object
{
public:
	Circle* circle = nullptr;
	Box* box = nullptr;
};

	class Circle : private Object
	{
	public:
		Vector2 position = Vector2();
		float radius = 0;
	};

	class Box : private Object
	{
	public:
		float length = 0;
		Vector2 position = Vector2();
	};

