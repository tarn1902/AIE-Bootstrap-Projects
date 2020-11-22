/*----------------------------------------
File Name: MathsLibrarySLL.h
Purpose: This is a statically linked 
library that holds data in the form of 
diffrent matrix and vectors within type of 
class. It also holds useful functions for 
doing maths on data.
Author: Tarn Cooper
Modified: 04 June 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include <cmath>
//Class for holding data in Vector2 form and it's math functions
template <typename T>
class Vec2
{
public:
	//-----------------------------------------------------------
	// Constructs a vector with values x and y.
	//	inX (T): What is x?
	//	inY (T): What is y?
	//-----------------------------------------------------------
	Vec2<T>(T inX, T inY)
	{
		x = inX;
		y = inY;
	}
	//-----------------------------------------------------------
	// Constructs a vector2 with values x and y being zero.
	//-----------------------------------------------------------
	Vec2<T>()
	{
		x = 0;
		y = 0;
	}
	//Creates a union of array with x and y.
	union
	{
		struct
		{
			T x, y;
		};
		T data[2];
	};
	//-----------------------------------------------------------
	// Operator overload of [] to access x and y through array
	//	index (int): What data in array to access?
	//	return (T): Returns data on position of index.
	//-----------------------------------------------------------
	T operator [] (int index) const
	{
		return data[index];
	}
	//-----------------------------------------------------------
	// Operator overload of + to add two vectors together.
	//	other (const Vec2<T>&): What vector to add?
	//	return (Vec2<T>): Returns result of adding two vectors.
	//-----------------------------------------------------------
	Vec2<T> operator + (const Vec2<T>& other) const
	{
		return { x + other.x, y + other.y };
	}
	//-----------------------------------------------------------
	// Operator overload of += to add a vector to current vector.
	//	other (const Vec2<T>&): What vector to add?
	//	return (Vec2<T>): Returns this class vector.
	//-----------------------------------------------------------
	Vec2<T> operator += (const Vec2<T>& other)
	{
		x += other.x; y += other.y;
		return *this;
	}
	//-----------------------------------------------------------
	// Operator overload of - to subtract two vectors from 
	//	eachother.
	//	other (const Vec2<T>&): What vector to subtract?
	//	return (Vec2<T>): Returns result of subtracting this 
	//						class vector from other vector.
	//-----------------------------------------------------------
	Vec2<T> operator - (const Vec2<T>& other) const
	{
		return{ x - other.x, y - other.y };
	}
	//-----------------------------------------------------------
	// Operator overload of -= to subtract a vector from 
	//	current vector.
	//	other (const Vec2<T>&): What vector to subtract?
	//	return (Vec2<T>): Returns this class vector.
	//-----------------------------------------------------------
	Vec2<T> operator -= (const Vec2<T>& other)
	{
		x -= other.x; y -= other.y;
		return *this;
	}
	//-----------------------------------------------------------
	// Operator overload of * to multiply this vector by a 
	//	scalar.  
	//	scalar (float): What to multiply vector by?
	//	return (Vec2<T>): Returns result of multiplying two 
	//						vectors together.
	//-----------------------------------------------------------
	Vec2<T> operator * (float scalar) const
	{
		return { x * scalar, y * scalar };
	}
	//-----------------------------------------------------------
	// Operator overload of * to multiply this vector by a 
	//	scalar. 
	//	scalar (float): What to multiply vector by?
	//	return (Vec2<T>): Returns this class vector.
	//-----------------------------------------------------------
	Vec2<T> operator *= (float scalar)
	{
		x *= scalar; y *= scalar;
		return *this;
	}
	//-----------------------------------------------------------
	// Operator overload of * to multiply a vector and scalar.
	//	scalar (const float): What scalar to multiply?
	//	other (const Vec2<T>&): What vector to multiply?
	//	return (Vec2<T>): Returns result of multiplying both.
	//-----------------------------------------------------------
	friend Vec2<T> operator * (const float scalar, const Vec2<T>& other)
	{
		return other * scalar;
	}
	//-----------------------------------------------------------
	// Operator overload of / to divide a vector by scalar 
	//	scalar (float): What to divide vector by?
	//	return (Vec2<T>): Returns result of dividing vector by 
	//						scalar.
	//-----------------------------------------------------------
	Vec2<T> operator / (const float scalar) const
	{
		return { x / scalar, y / scalar };
	}
	//-----------------------------------------------------------
	// Operator overload of /= to divide a this class vector by a 
	//	scalar.
	//	scalar (float): What to divide this class vector by?
	//	return (Vec2<T>): Returns results of divide this class 
	//						vector by scalar
	//-----------------------------------------------------------
	Vec2<T> operator /= (float scalar)
	{
		x /= scalar; y /= scalar;;
		return *this;
	}
	//-----------------------------------------------------------
	// Operator overload of / to divide a vector by scalar 
	//	scalar (const float): What to divide vector by?
	//	other (const Vec2<T>&): What vector to divide?
	//	return (Vec2<T>): Returns result of dividing a vector 
	//						by scalar.
	//-----------------------------------------------------------
	friend Vec2<T> operator / (const float scalar, const Vec2<T>& other)
	{
		return other / scalar;
	}
	//-----------------------------------------------------------
	// Operator overload of = to set this class vector to other 
	//	vector.
	//	other (const Vec2<T>&): What vector to set this class 
	//							to?
	//	return (Vec2<T>): Returns result this class vector.
	//-----------------------------------------------------------
	Vec2<T>& operator = (const Vec2<T>& other)
	{
		x = other.x; y = other.y;
		return *this;
	}
	//-----------------------------------------------------------
	// Operator overload of float*() to return a float pointer to
	//	data.
	//	return (float*): Returns a float pointer to data.
	//-----------------------------------------------------------
	explicit operator float*()
	{
		return (float*)data;
	}
	//-----------------------------------------------------------
	// A function for finding dot product of this class vector 
	//	and other.
	//	other (const Vec2<T>&): What vector to dot product with?
	//	return (float): Returns results of doing a dot product.
	//	Formula: A DOT B = Ax * Bx + Ay * By.
	//-----------------------------------------------------------
	float dot(const Vec2<T>& other) const
	{
		return x * other.x + y * other.y;
	}
	//-----------------------------------------------------------
	// A function for finding magnitude of this class vector.
	//	return (float): Returns results of finding a dot product.
	//	Formula: ||A|| = sqrt(Ax * Ax + Ay * Ay).
	//-----------------------------------------------------------
	float magnitude() const
	{
		return (T)sqrt(x*x + y * y);
	}
	//-----------------------------------------------------------
	// A function for finding magnitude of this class vector 
	//	without using sqr. 
	//	return (float): Returns results of finding magnitude.
	//	Formula: ||A * A|| = Ax * Ax + Ay * Ay.
	//-----------------------------------------------------------
	float magnitudeSqr() const
	{
		return x * x + y * y;
	}
	//-----------------------------------------------------------
	// A function for finding distance of two vectors. 
	//	return (float): Returns results finding distance.
	//	Formula: D = magnitude(A - B).
	//-----------------------------------------------------------
	float distance(const Vec2<T>& other) const
	{
		float diffX = x - other.x;
		float diffY = y - other.y;
		return (float)sqrt(diffX * diffX + diffY * diffY);
	}
	//-----------------------------------------------------------
	// A function for normailising this class vector, so 
	//	magnitude is equal to one.
	//	Formula: A^ = (Ax / magnitude(A), Ay / magnitude(A)).
	//-----------------------------------------------------------
	void normalise()
	{
		float mag = (float)sqrt(x * x + y * y);
		x /= mag;
		y /= mag;
	}
	//-----------------------------------------------------------
	// A function for normailising this class vector, so 
	//	magnitude is equal to one.
	//	return (Vec2<T>): returns the normalised vector of this 
	//						class vector.
	//	Formula: A^ = (Ax / magnitude(A), Ay / magnitude(A)).
	//-----------------------------------------------------------
	Vec2<T> normalised() const
	{
		float mag = (float)sqrt(x * x + y * y);
		return { x / mag, y / mag };
	}
	//-----------------------------------------------------------
	// A function for getting a perpendicular vector to this 
	//	class vector on right-hand side.
	//	return (Vec2<T>): returns the vector right-hand 
	//						perpendicular to this class vector.
	//	Formula: B = (-Ay, Ax).
	//-----------------------------------------------------------
	Vec2<T> getPerpendicularRH() const
	{
		return { -y, x };
	}	/*-----------------------------------------------------------
	// A function for getting a perpendicular vector to this
	//	class vector on left-hand side
	//	return (Vec2<T>): returns the vector left-hand
	//						perpendicular to this class vector
	//	Formula: B = (Ay, -Ax).
	//---------------------------------------------------------*/	Vec2<T> getPerpendicularLH() const
	{
		return { y, -x };
	}	/*-----------------------------------------------------------
	// A function for getting angle between this class vector and 
	//	another.
	//	other (const Vec2<T>&): What is the other vector to 
	//							compare.
	//	return (float): returns angle between two vectors.
	//	Formula: 0 = acos(A^ DOT A^).
	//----------------------------------------------------------*/	float angleBetween(const Vec2<T>& other) const
	{
		Vec2<T> a = normalised();
		Vec2<T> b = other.normalised();
		float d = a.x * b.x + a.y * b.y;
		return (float)acos(d);
	}
};
//Class for holding data in Vector3 form and it's math functions
template <typename T>
class Vec3
{
public:
//-----------------------------------------------------------
// Constructs a vector with values x, y and z.
//	inX (T): What is x?
//	inY (T): What is y?
//	inZ(T) : What is z?
//-----------------------------------------------------------
	Vec3<T>(T inX, T inY, T inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}
//-----------------------------------------------------------
// Constructs a vector2 with values x, y and z being zero.
//-----------------------------------------------------------
	Vec3<T>()
	{
		x = 0;
		y = 0;
		z = 0;
	}
//Creates a union of array with x, y and z.
	union
	{
		struct
		{
			T x, y, z;
		};
		T data[3];
	};
//-----------------------------------------------------------
// Operator overload of [] to access x, y and z through array
//	index (int): What data in array to access?
//	return (T): Returns data on position of index.
//-----------------------------------------------------------
	T operator [] (int index) const
	{
		return data[index];
	}
//-----------------------------------------------------------
// Operator overload of + to add two vectors together.
//	other (const Vec3<T>&): What vector to add?
//	return (Vec3<T>): Returns result of adding two vectors 
//-----------------------------------------------------------
	Vec3<T> operator + (const Vec3<T>& other) const
	{
		return { x + other.x, y + other.y, z + other.z };
	}
//-----------------------------------------------------------
// Operator overload of += to add a vector to current vector.
//	other (const Vec3<T>&): What vector to add?
//	return (Vec3<T>): Returns this class.
//-----------------------------------------------------------
	Vec3<T> operator += (const Vec3<T>& other) 
	{
		x += other.x; y += other.y; z += other.z;
		return *this;
	}
//-----------------------------------------------------------
// Operator overload of - to subtract two vectors from 
//	eachother.
//	other (const Vec3<T>&): What vector to subtract?
//	return (Vec3<T>): Returns result of subtracting this 
//						class vector from other vector.
//-----------------------------------------------------------
	Vec3<T> operator - (const Vec3<T>& other) const
	{
		return{ x - other.x, y - other.y, z - other.z };
	}
//-----------------------------------------------------------
// Operator overload of -= to subtract a vector from 
//	current vector.
//	other (const Vec3<T>&): What vector to subtract?
//	return (Vec3<T>): Returns this class vector.
//-----------------------------------------------------------
	Vec3<T> operator -= (const Vec3<T>& other) 
	{
		x -= other.x; y -= other.y; z -= other.z;
		return *this;
	}
//-----------------------------------------------------------
// Operator overload of * to multiply this vector by a 
//	scalar. 
//	scalar (float): What to multiply vector by?
//	return (Vec3<T>): Returns result of multiplying this
//						vectors by scalar.
//-----------------------------------------------------------
	Vec3<T> operator * (float scalar) const
	{
		return { x * scalar, y * scalar, z * scalar };
	}
//-----------------------------------------------------------
// Operator overload of *= to multiply a vectors from current 
//	vector.
//	scalar (float): What to multiply vector by?
//	return (Vec3<T>): Returns this class vector.
//-----------------------------------------------------------
	Vec3<T> operator *= (float scalar) 
	{
		x *= scalar; y *= scalar; z *= scalar;
		return *this;
	}
//-----------------------------------------------------------
// Operator overload of * to multiply a vector and scalar.
//	scalar (const float): What scalar to multiply?
//	other (const Vec3<T>&): What vector to multiply?
//	return (Vec3<T>): Returns result of multiplying both.
//-----------------------------------------------------------
	friend Vec3<T> operator * (const float scalar, const Vec3<T>& other)
	{
		return other * scalar;
	}
//-----------------------------------------------------------
// Operator overload of / to divide a vector by scalar.
//	scalar (const float): What to divide vector by?
//	other (const Vec3<T>&): What vector to divide?
//	return (Vec3T>): Returns result of dividing a vector 
//						by scalar.
//-----------------------------------------------------------
	Vec3<T> operator / (float scalar) const
	{
		return { x / scalar, y / scalar, z / scalar };
	}
//-----------------------------------------------------------
// Operator overload of /= to divide a this class vector by a 
//	scalar.
//	scalar (float): What to divide this class vector by?
//	return (Vec3<T>): Returns results of divide this class 
//						vector by scalar.
//-----------------------------------------------------------
	Vec3<T> operator /= (float scalar)
	{
		x /= scalar; y /= scalar; z /= scalar;
		return *this;
	}
//-----------------------------------------------------------
// Operator overload of = to set this class vector to other 
//	vector.
//	other (const Vec3<T>&): What vector to set this class 
//							to?
//	return (Vec3<T>): Returns result this class vector.
//-----------------------------------------------------------
	Vec3<T>& operator = (const Vec3<T>& other)
	{
		x = other.x; y = other.y; z = other.z;
		return *this;
	}
//-----------------------------------------------------------
// Operator overload of float*() to return a float pointer to
//	data.
//	return (float*): Returns a float pointer to data.
//-----------------------------------------------------------
	explicit operator float*()
	{
		return (float*)data;
	}
//-----------------------------------------------------------
// Operator overload of Vec2<T>() to return a Vec2<T>.
//	return (Vec2<T>()): Returns a Vec2<T> using x and y.
//-----------------------------------------------------------
	operator Vec2<T>()
	{
		return { x, y };
	}
//-----------------------------------------------------------
// A function for finding dot product of this class vector 
//	and other.
//	other (const Vec3<T>&): What vector to dot product with?
//	return (float): Returns results of doing a dot product.
//	Formula: A DOT B = Ax * Bx + Ay * By + Az + Bz.
//-----------------------------------------------------------
	float dot(const Vec3<T>& other) const {
		return x * other.x + y * other.y + z * other.z;
	}
//-----------------------------------------------------------
// A function for finding distance of two vectors.
//	return (float): Returns results finding distance.
//	Formula: D = magnitude(A - B).
//-----------------------------------------------------------
	float distance(const Vec3<T>& other) const {
		float diffX = x - other.x;
		float diffY = y - other.y;
		float diffZ = z - other.z;
		return (T)sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
	}
//-----------------------------------------------------------
// A function for finding magnitude of this class vector.
//	return (float): Returns results of finding a dot product.
//	Formula: ||A|| = sqrt(Ax * Ax + Ay * Ay + Az* Az).
//-----------------------------------------------------------
	float magnitude() const
	{
		return (T)sqrt(x*x + y * y + z * z);
	}
//-----------------------------------------------------------
// A function for finding magnitude of this class vector 
//	without using sqr. 
//	return (float): Returns results of finding magnitude.
//	Formula: ||A * A|| = Ax * Ax + Ay * Ay+ Az * Az).
//-----------------------------------------------------------
	float magnitudeSqr() const
	{
		return x * x + y * y + z * z;
	}
//-----------------------------------------------------------
// A function for normailising this class vector, so 
//	magnitude is equal to one.
//	Formula: A^ = (Ax / magnitude(A), Ay / magnitude(A), 
//					Az / magnitude(A)).
//-----------------------------------------------------------
	void normalise() {
		float mag = (T)sqrt(x * x + y * y + z * z);
		x /= mag;
		y /= mag;
		z /= mag;
	}
//-----------------------------------------------------------
// A function for normailising this class vector, so 
//	magnitude is equal to one.
//	return (Vec3<T>): returns the normalised vector of this 
//						class vector.
//	Formula: A^ = (Ax / magnitude(A), Ay / magnitude(A),
//					Az / magnitude(A)).
//-----------------------------------------------------------
	Vec3<T> normalised() const {
		float mag = (T)sqrt(x * x + y * y + z * z);
		return { x / mag, y / mag, z / mag };
	}
//-----------------------------------------------------------
// A function for creating a third vector perpendicular to
// two perpendicular vectors.
//	other (Vec3<T>): What is the other perpendicular vector.
//	return (Vec3<T>): returns third perpendicular vector.
//	Formula: AxB = [AyBz - AzBy]
//				   [AzBx - AxBz]
//				   [AxBy - AyBx].
//-----------------------------------------------------------
	Vec3<T> cross(const Vec3<T>& other) const
	{
		return
		{
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		};
	}
//-----------------------------------------------------------
// A function for getting angle between this class vector and 
//	another.
//	other (const Vec3<T>&): What is the other vector to 
//							compare.
//	return (float): returns angle between two vectors.
//	Formula: 0 = acos(A^ DOT A^).
//-----------------------------------------------------------
	float angleBetween(const Vec3<T>& other) const {
		Vec3<T> a = normalised();
		Vec3<T> b = other.normalised();
		float d = a.x * b.x + a.y * b.y + a.z * b.z;
		return (T)acos(d);
	}
};
//Class for holding data in Vector4 form and it's math functions
template <typename T>
class Vec4
{
public:
//-----------------------------------------------------------
// Constructs a vector with values x, y, z and w.
//	inX (T): What is x?
//	inY (T): What is y?
//	inZ (T): What is z?
//	inW (T): What is w?
//-----------------------------------------------------------
	Vec4<T>(T inX, T inY, T inZ, T inW)
	{

		x = inX;
		y = inY;
		z = inZ;
		w = inW;
	}
//-----------------------------------------------------------
// Constructs a vector2 with values x, y, z and w being zero.
//-----------------------------------------------------------
	Vec4<T>()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
//Creates a union of array with x, y, z and w.
	union
	{
		struct
		{
			T x, y, z, w;
		};
		T data[4];
	};
//-----------------------------------------------------------
// Operator overload of [] to access x, y, z and w through 
//	array
//	index (int): What data in array to access?
//	return (T): Returns data on position of index.
//-----------------------------------------------------------
	T operator [] (int index) const
	{
		return data[index];
	}
//-----------------------------------------------------------
// Operator overload of + to add two vectors together.
//	other (const Vec4<T>&): What vector to add?
//	return (Vec4<T>): Returns result of adding two vectors.
//-----------------------------------------------------------
	Vec4<T> operator + (const Vec4<T>& other) const
	{
		return { x + other.x, y + other.y, z + other.z, w + other.w };
	}
//-----------------------------------------------------------
// Operator overload of += to add a vector to current vector.
//	other (const Vec4<T>&): What vector to add?
//	return (Vec4<T>): Returns this class vector.
//-----------------------------------------------------------
	Vec4<T> operator += (const Vec4<T>& other) const
	{
		x += other.x; y += other.y; z += other.z; w += other.w;
		return *this;
	}
//-----------------------------------------------------------
// Operator overload of - to subtract two vectors from 
//	eachother.
//	other (const Vec4<T>&): What vector to subtract?
//	return (Vec4<T>): Returns result of subtracting this 
//						class vector from other vector.
//-----------------------------------------------------------
	Vec4<T> operator - (const Vec4<T>& other) const
	{
		return{ x - other.x, y - other.y, z - other.z, w - other.w };
	}
//-----------------------------------------------------------
// Operator overload of -= to subtract a vector from 
//	current vector.
//	other (const Vec4<T>&): What vector to subtract?
//	return (Vec4<T>): Returns this class vector.
//-----------------------------------------------------------
	Vec4<T> operator -= (const Vec4<T>& other) const
	{
		x -= other.x; y -= other.y; z -= other.z; w -= other.w;
		return *this;
	}
//-----------------------------------------------------------
// Operator overload of * to multiply this vector by a 
//	scalar.  
//	scalar (float): What to multiply vector by?
//	return (Vec4<T>): Returns result of multiplying two 
//						vectors.
//-----------------------------------------------------------
	Vec4<T> operator * (float scalar) const
	{
		return { x * scalar, y * scalar, z * scalar, w * scalar };
	}
//-----------------------------------------------------------
// Operator overload of * to multiply this vector by a 
//	scalar. 
//	scalar (float): What to multiply vector by?
//	return (Vec4<T>): Returns this class vector.
//-----------------------------------------------------------
	Vec4<T> operator *= (float scalar) const
	{
		x *= scalar; y *= scalar; z *= scalar; w *= scalar;
		return *this;
	}
//-----------------------------------------------------------
// Operator overload of * to multiply a vector and scalar.
//	scalar (const float): What scalar to multiply?
//	other (const Vec4<T>&): What vector to multiply?
//	return (Vec4<T>): Returns result of multiplying both.
//-----------------------------------------------------------
	friend Vec4<T> operator * (const float scalar, const Vec4<T>& other)
	{
		return other * scalar;
	}
//-----------------------------------------------------------
// Operator overload of / to divide a vector by scalar 
//	scalar (float): What to divide vector by?
//	return (Vec4<T>): Returns result of dividing vector by 
//						scalar.
//-----------------------------------------------------------
	Vec4<T> operator / (float scalar)
	{
		return { x / scalar, y / scalar, z / scalar, w / scalar };
	}
//-----------------------------------------------------------
// Operator overload of /= to divide a this class vector by a 
//	scalar.
//	scalar (float): What to divide this class vector by?
//	return (Vec4<T>): Returns results of divide this class 
//						vector by scalar
//-----------------------------------------------------------
	Vec4<T> operator /= (float scalar)
	{
		x /= scalar; y /= scalar; z /= scalar; w /= scalar;
		return *this;
	}
//-----------------------------------------------------------
// Operator overload of = to set this class vector to other 
//	vector.
//	other (const Vec4<T>&): What vector to set this class 
//							to?
//	return (Vec4<T>): Returns result this class vector.
//-----------------------------------------------------------
	Vec4<T>& operator = (const Vec4<T>& other)
	{
		x = other.x; y = other.y; z = other.z; w = other.w;
		return *this;
	}
//-----------------------------------------------------------
// Operator overload of float*() to return a float pointer to
//	data.
//	return (float*): Returns a float pointer to data.
//-----------------------------------------------------------
	explicit operator float*()
	{
		return (float*)data;
	}
//-----------------------------------------------------------
// Operator overload of Vec2<T>() to return a Vec2<T>.
//	return (Vec2<T>()): Returns a Vec2<T> using x and y.
//-----------------------------------------------------------
	operator Vec2<T>()
	{
		return { x, y};
	}
//-----------------------------------------------------------
// Operator overload of Vec3<T>() to return a Vec2<T>.
//	return (Vec3<T>()): Returns a Vec2<T> using x, y and z.
//-----------------------------------------------------------
	operator Vec3<T>()
	{
		return { x, y, z};
	}
//-----------------------------------------------------------
// A function for finding dot product of this class vector 
//	and other.
//	other (const Vec4<T>&): What vector to dot product with?
//	return (float): Returns results of doing a dot product.
//	Formula: A DOT B = Ax * Bx + Ay * By + Az * Bz + Aw * Bw.
//-----------------------------------------------------------
	float dot(const Vec4<T>& other) const {
		return (T)(x * other.x + y * other.y + z * other.z + w * other.w);
	}
//-----------------------------------------------------------
// A function for finding distance of two vectors. 
//	return (float): Returns results finding distance.
//	Formula: D = magnitude(A - B).
//-----------------------------------------------------------
	float distance(const Vec4<T>& other) const {
		float diffX = x - other.x;
		float diffY = y - other.y;
		float diffZ = z - other.z;
		float diffW = w - other.w;
		return (T)sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ + diffW * diffW);
	}
//-----------------------------------------------------------
// A function for finding magnitude of this class vector.
//	return (float): Returns results of finding a dot product.
//	Formula: ||A|| = sqrt(Ax * Ax + Ay * Ay + Az * Az + Aw * Aw).
//-----------------------------------------------------------
	float magnitude() const
	{
		return (T)sqrt(x * x + y * y + z * z + w * w);
	}
//-----------------------------------------------------------
// A function for finding magnitude of this class vector
// without sqr()
//	return (float): Returns results of finding a dot product.
//	Formula: ||A*A|| = Ax * Ax + Ay * Ay + Az * Az + Aw * Aw)
//-----------------------------------------------------------
	float magnitudeSqr() const
	{
		return (T)sqrt(x * x + y * y + z * z + w * w);
	}
//-----------------------------------------------------------
// A function for normailising this class vector, so 
//	magnitude is equal to one.
//	Formula: A^ = (Ax / magnitude(A), Ay / magnitude(A), 
//					Az / magnitude(A), Aw / magnitude(A)).
//-----------------------------------------------------------
	void normalise() {
		float mag = (T)sqrt(x * x + y * y + z * z + w * w);

		x /= mag;
		y /= mag;
		z /= mag;
		w /= mag;
	}
//-----------------------------------------------------------
// A function for normailising this class vector, so 
//	magnitude is equal to one.
//	return (Vec4<T>): returns the normalised vector of this 
//						class vector.
//	Formula: A^ = (Ax / magnitude(A), Ay / magnitude(A), 
//					Az / magnitude(A), Aw / magnitude(A)).
//-----------------------------------------------------------
	Vec4<T> normalised() const {
		float mag = (T)sqrt(x * x + y * y + z * z + w * w);
		return { x / mag, y / mag, z / mag, w / mag };
	}

//-----------------------------------------------------------
// A function for creating a third vector perpendicular to
// two perpendicular vectors.
//	other (Vec4<T>): What is the other perpendicular vector.
//	return (Vec4<T>): returns third perpendicular vector.
//	Formula: AxB = [AyBz - AzBy]
//				   [AzBx - AxBz]
//				   [AxBy - AyBx]
//				   [	 0	   ].
//-----------------------------------------------------------
	Vec4<T> cross(const Vec4<T>& other) const
	{
		return
		{
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x, 
			0
		};
	}
};
//Class for holding data in Matrix3 form and it's math functions.
template <typename T>
class Mat3
{
public:
//Creates a union of a 2d array, vector3 and x, y and z axis.
	union
	{
		struct
		{
			Vec3<T> xAxis;
			Vec3<T> yAxis;
			Vec3<T> zAxis;
		};
		Vec3<T> axis[3];
		T data[3][3];
	};
//-----------------------------------------------------------
// Constructs a identity matrix for matrix3
//-----------------------------------------------------------
	Mat3<T>()
	{
		xAxis = { 1,0,0 };
		yAxis = { 0,1,0 };
		zAxis = { 0,0,1 };
	}
//-----------------------------------------------------------
// Function for creating a identity matrix for matrix3.
//	return (Mat3<T>): Construct to identity matrix.
//-----------------------------------------------------------
	Mat3<T> Identity()
	{
		return Mat3<T>();
	}
	//-----------------------------------------------------------
	// Constructs a matrix3 with a list of values to fill matrix
	//	xx (T): What is xx?
	//	xy (T): What is xy?
	//	xz (T): What is xz?
	//	yx (T): What is yx?
	//	yy (T): What is yy?
	//	yz (T): What is yz?
	//	zx (T): What is zx?
	//	zy (T): What is zy?
	//	zz (T): What is zz?
	//-----------------------------------------------------------
	Mat3<T>(T xx, T xy, T xz, T yx, T yy, T yz, T zx, T zy, T zz)
	{
		xAxis = { xx, xy, xz };
		yAxis = { yx, yy, yz };
		zAxis = { zx, zy, zz };
	}
//-----------------------------------------------------------
// Operator overload of [] to access x, y and z through array
//	index (int): What data in array to access?
//	return (Vec3<T>&): Returns axis on position of index.
//-----------------------------------------------------------
	Vec3<T>& operator [] (int index)
	{
		return axis[index];
	}
//-----------------------------------------------------------
// Operator overload of * to multiply two matrix3.
//	other (const Mat3<T>&): What is the other matrix3?
//	return (Mat3<T>): Returns results of muliplication
//	Formula: Am DOT Bn = Mmn
//-----------------------------------------------------------
	Mat3<T>  operator * (const Mat3<T>& other) const
	{
		Mat3<T> result;
		for (int r = 0; r < 3; ++r)
		{
			for (int c = 0; c < 3; ++c)
			{
				result.data[c][r] = data[0][r] * other.data[c][0] + data[1][r] * other.data[c][1] + data[2][r] * other.data[c][2];
			}
		}
		return result;
	}
//-----------------------------------------------------------
// Operator overload of * to multiply a matrix3 and vector3.
//	other (const Vec3<T>&): What is the other vector3?
//	return (Vec3<T>): Returns results of multiplication.
//	Formula: Am DOT Bn = Mmn
//-----------------------------------------------------------
	Vec3<T> operator * (const Vec3<T> other) const
	{
		Vec3<T> result;
		for (int r = 0; r < 3; ++r)
		{
			result.data[r] = data[0][r] * other.data[0] + data[1][r] * other.data[1] + data[2][r] * other.data[2];
		}
		return result;
	}
//-----------------------------------------------------------
// Operator overload of = to set this class matrix3 to other 
//	matrix3.
//	other (const Mat3<T>&): What matrix3 to set this class 
//							to?
//	return (Mat3<T>): Returns result this class matrix3.
//-----------------------------------------------------------
	Mat3<T>& operator = (const Mat3<T>& other)
	{
		xAxis.x = other.xAxis.x, xAxis.y = other.xAxis.y, xAxis.z = other.xAxis.z, yAxis.x = other.yAxis.x, yAxis.y = other.yAxis.y, yAxis.z = other.yAxis.z, zAxis.x = other.zAxis.x, zAxis.y = other.zAxis.y, zAxis.z = other.zAxis.z;
		return *this;
	}
//-----------------------------------------------------------
// A function for switching between column major and row 
//	major matrix3.
//	return (Mat3<T>): Returns results of transposition.
//  Formula: M = [A B C]	Mt = [A D G]
//				 [D E F]		 [B E H]
//				 [G H I] 		 [C F I]
//-----------------------------------------------------------
	Mat3<T>  transposed() const
	{
		Mat3<T> result;
		for (int r = 0; r < 3; ++r)
			for (int c = 0; c < 3; ++c)
				result.data[r][c] = data[c][r];
		return result;
	}
//-----------------------------------------------------------
// Operator overload of float*() to return a float pointer to
//	data.
//	return (float*): Returns a float pointer to data.
//-----------------------------------------------------------
	explicit operator float*()
	{
		return (float*)data;
	}
//-----------------------------------------------------------
// Function for creating a matrix for rotating x.
//	radians (float): How many radians to rotate?
//	Formula: [1       0      0]
//			 [0  cos(a) sin(a)]
//			 [0 -sin(a) cos(a)]
//-----------------------------------------------------------
	void setRotateX(float radians)
	{
		xAxis = { 1, 0, 0 };
		yAxis = { 0, cosf(radians), sinf(radians) };
		zAxis = { 0, -sinf(radians), cosf(radians) };
	}
//-----------------------------------------------------------
// Function for rotating x axis of object.
//	radians (float): How many radians to rotate?
//-----------------------------------------------------------
	void rotateX(float radians) 
	{ 
		Mat3<T> m; 
		m.setRotateX(radians); 
		*this = *this * m; 
	}
//-----------------------------------------------------------
// Function for creating a matrix for rotating y.
//	radians (float): How many radians to rotate?
//	Formula: [cos(a) 0 -sin(a)]
//			 [0      1       0]
//			 [sin(a) 0  cos(a)]
//-----------------------------------------------------------
	void setRotateY(float radians)
	{
		xAxis = { cosf(radians), 0, -sinf(radians) };
		yAxis = { 0, 1, 0 };
		zAxis = { sinf(radians), 0, cosf(radians) };
	}
//-----------------------------------------------------------
// Function for rotating y axis of object.
//	radians (float): How many radians to rotate?
//-----------------------------------------------------------
	void rotateY(float radians)
	{
		Mat3<T> m;
		m.setRotateY(radians);
		*this = *this * m;
	}
//-----------------------------------------------------------
// Function for creating a matrix for rotating z.
//	radians (float): How many radians to rotate?
//	Formula: [cos(a)  sin(a) 0]
//			 [-sin(a) cos(a) 0]
//			 [0       0      1]
//-----------------------------------------------------------
	void setRotateZ(float radians)
	{
		xAxis = { cosf(radians), sinf(radians), 0 };
		yAxis = { -sinf(radians), cosf(radians), 0 };
		zAxis = { 0, 0, 1 };
	}
//-----------------------------------------------------------
// Function for rotating z axis of object.
//	radians (float): How many radians to rotate?
//-----------------------------------------------------------
	void rotateZ(float radians)
	{
		Mat3<T> m;
		m.setRotateZ(radians);
		*this = *this * m;
	}
//-----------------------------------------------------------
// Function for creating a matrix for scaling a object.
//	x (float): how many times bigger in x?
//	y (float): how many times bigger in y?
//	z (float): how many times bigger in z?
//	Formula: [x  0  0]
//			 [0  y  0]
//			 [0  0  z]
//-----------------------------------------------------------
	void setScaled(float x, float y, float z) 
	{ 
		xAxis = { x, 0, 0 }; 
		yAxis = { 0, y, 0 }; 
		zAxis = { 0, 0, z }; 
	}
//-----------------------------------------------------------
// Function for scaling a object.
//	x (float): how many times bigger in x?
//	y (float): how many times bigger in y?
//	z (float): how many times bigger in z?
//-----------------------------------------------------------
	void scale(float x, float y, float z)
	{
		Mat3<T> m;
		m.setScaled(x, y, z);
		*this = *this * m;
	}
	//-----------------------------------------------------------
	// Function for creating a matrix for translating a object.
	//	x (float): how much in x direction?
	//	y (float): how much in y direction?
	//	Formula: [1  0  0]
	//			 [0  1  0]
	//			 [x  y  1]
	//-----------------------------------------------------------
	void setTranslate(float x, float y)
	{
		xAxis = { 1, 0, 0 };
		yAxis = { 0, 1, 0 };
		zAxis = { x, y, 1 };
	}
	//-----------------------------------------------------------
	// Function for translating a object.
	//	x (float): how many times bigger in x?
	//	y (float): how many times bigger in y?
	//-----------------------------------------------------------
	void translate(float x, float y)
	{
		Mat3<T> m;
		m.setTranslate(x, y);
		*this = *this * m;
	}
};
//Class for holding data in Matrix3 form and it's math functions.
template <typename T>
class Mat4
{	
public:
	//Creates a union of a 2d array, vector4 and x, y, z and w axis.
	union
	{
		struct
		{
			Vec4<T> xAxis;
			Vec4<T> yAxis;
			Vec4<T> zAxis;
			Vec4<T> wAxis;
			
		};
		Vec4<T> axis[4];
		T data[4][4];
	};
//-----------------------------------------------------------
// Constructs a identity matrix for matrix4
//-----------------------------------------------------------
	Mat4<T>()
	{

		xAxis = { 1,0,0,0 };
		yAxis = { 0,1,0,0 };
		zAxis = { 0,0,1,0 };
		wAxis = { 0,0,0,1 };
	}
//-----------------------------------------------------------
// Function for creating a identity matrix for matrix3.
//	return (Mat4<T>): Construct to identity matrix.
//-----------------------------------------------------------
	Mat4<T> Identity()
	{
		return Mat4<T>();
	}
//-----------------------------------------------------------
// Constructs a matrix4 with a list of values to fill matrix
//	xx (T): What is xx?
//	xy (T): What is xy?
//	xz (T): What is xz?
//	xw (T): What is xw?
//	yx (T): What is yx?
//	yy (T): What is yy?
//	yz (T): What is yz?
//	yw (T): What is yw?
//	zx (T): What is zx?
//	zy (T): What is zy?
//	zz (T): What is zz?
//	zz (T): What is zw?
//	wx (T): What is wx?
//	wy (T): What is wy?
//	wz (T): What is wz?
//	wz (T): What is ww?
//-----------------------------------------------------------
	Mat4<T>(T xx, T xy, T xz, T xw, T yx, T yy, T yz, T yw, T zx, T zy, T zz, T zw, T wx, T wy, T wz, T ww)
	{
		xAxis = { xx, xy, xz, xw };
		yAxis = { yx, yy, yz, yw };
		zAxis = { zx, zy, zz, zw };
		wAxis = { wx, wy, wz, ww };
	}
//-----------------------------------------------------------
// Operator overload of [] to access x, y, z and w through 
//	array
//	index (int): What data in array to access?
//	return (Vec4<T>&): Returns axis on position of index.
//-----------------------------------------------------------
	Vec4<T>& operator [] (int index)
	{
		return axis[index];
	}
//-----------------------------------------------------------
// Operator overload of * to multiply two matrix4.
//	other (const Mat4<T>&): What is the other matrix4?
//	return (Mat4<T>): Returns results of muliplication
//	Formula: Am DOT Bn = Mmn
//-----------------------------------------------------------
	Mat4<T>  operator * (const Mat4<T>& other) const
	{
		Mat4<T> result;
		for (int r = 0; r < 4; ++r)
		{
			for (int c = 0; c < 4; ++c)
			{
				result.data[c][r] = data[0][r] * other.data[c][0] + data[1][r] * other.data[c][1] + data[2][r] * other.data[c][2] + data[3][r] * other.data[c][3];
			}
		}
		return result;
	}
//-----------------------------------------------------------
// Operator overload of * to multiply a matrix4 and vector4.
//	other (const Vec4<T>&): What is the other vector3?
//	return (Vec4<T>): Returns results of multiplication.
//	Formula: Am DOT Bn = Mmn
//-----------------------------------------------------------
	Vec4<T> operator * (const Vec4<T> other) const
	{
		Vec4<T> result; 
		for (int r = 0; r < 4; ++r) 
		{ 
			result.data[r] = data[0][r] * other.data[0] + data[1][r] * other.data[1] + data[2][r] * other.data[2] + data[3][r] * other.data[3];
		} 
		return result;
	}
	//-----------------------------------------------------------
// Operator overload of = to set this class matrix4 to other 
//	matrix4.
//	other (const Mat4<T>&): What matrix4 to set this class 
//							to?
//	return (Mat4<T>): Returns result this class matrix4.
//-----------------------------------------------------------
	Mat4<T>& operator = (const Mat4<T>& other)
	{
		xAxis.x = other.xAxis.x, xAxis.y = other.xAxis.y, xAxis.z = other.xAxis.z, xAxis.w = other.xAxis.w, yAxis.x = other.yAxis.x, yAxis.y = other.yAxis.y, yAxis.z = other.yAxis.z, yAxis.w = other.yAxis.w, zAxis.x = other.zAxis.x, zAxis.y = other.zAxis.y, zAxis.z = other.zAxis.z, zAxis.w = other.zAxis.w, wAxis.x = other.wAxis.x, wAxis.y = other.wAxis.y, wAxis.z = other.wAxis.z, wAxis.w = other.wAxis.w;
		return *this;
	}
//-----------------------------------------------------------
// A function for switching between column major and row 
//	major matrix4.
//	return (Mat4<T>): Returns results of transposition.
//  Formula: M = [A B C D]	Mt = [A E I M]
//				 [E F G H]		 [B F J N]
//				 [I J K L] 		 [C G K O]
//			   	 [M N O P]		 [D H L P]
//-----------------------------------------------------------
	Mat4<T>  transposed() const
	{
		Mat4<T> result;
		for (int r = 0; r < 4; ++r)
			for (int c = 0; c < 4; ++c)
				result.data[r][c] = data[c][r];
		return result;
	}
//-----------------------------------------------------------
// Operator overload of float*() to return a float pointer to
//	data.
//	return (float*): Returns a float pointer to data.
//-----------------------------------------------------------
	explicit operator float*()
	{
		return (float*)data;
	}
//-----------------------------------------------------------
// Function for creating a matrix for rotating x.
//	radians (float): How many radians to rotate?
//	Formula: [1       0      0	0]
//			 [0  cos(a) sin(a)	0]
//			 [0 -sin(a) cos(a)	0]
//			 [0      0		0	1]
//-----------------------------------------------------------
	void setRotateX(float radians)
	{
		xAxis = { 1, 0, 0, 0 };
		yAxis = { 0, cosf(radians), sinf(radians), 0 };
		zAxis = { 0, -sinf(radians), cosf(radians), 0 };
		wAxis = { 0, 0, 0, 1 };
	}
	//-----------------------------------------------------------
	// Function for rotating x axis of object.
	//	radians (float): How many radians to rotate?
	//-----------------------------------------------------------
	void rotateX(float radians)
	{
		Mat4<T> m;
		m.setRotateX(radians);
		*this = *this * m;
	}
//-----------------------------------------------------------
// Function for creating a matrix for rotating y.
//	radians (float): How many radians to rotate?
//	Formula: [cos(a) 0 -sin(a) 0]
//			 [0      1       0 0]
//			 [sin(a) 0  cos(a) 0]
//			 [0		 0	0	   1]
//-----------------------------------------------------------
	void setRotateY(float radians)
	{
		xAxis = { cosf(radians), 0, -sinf(radians), 0 };
		yAxis = { 0, 1, 0, 0 };
		zAxis = { sinf(radians), 0, cosf(radians), 0 };
		wAxis = { 0, 0, 0, 1 };
	}
//-----------------------------------------------------------
// Function for rotating y axis of object.
//	radians (float): How many radians to rotate?
//-----------------------------------------------------------
	void rotateY(float radians)
	{
		Mat4<T> m;
		m.setRotateY(radians);
		*this = *this * m;
	}
//-----------------------------------------------------------
// Function for creating a matrix for rotating z.
//	radians (float): How many radians to rotate?
//	Formula: [cos(a)  sin(a) 0 0]
//			 [-sin(a) cos(a) 0 0]
//			 [0       0      1 0]
//		     [0       0      0 1]
//-----------------------------------------------------------
	void setRotateZ(float radians)
	{
		xAxis = { cosf(radians), sinf(radians), 0, 0 };
		yAxis = { -sinf(radians), cosf(radians), 0, 0 };
		zAxis = { 0, 0, 1, 0 };
		wAxis = { 0,0,0,1 };
	}
//-----------------------------------------------------------
// Function for rotating z axis of object.
//	radians (float): How many radians to rotate?
//-----------------------------------------------------------
	void rotateZ(float radians)
	{
		Mat4<T> m;
		m.setRotateZ(radians);
		*this = *this * m;
	}
//-----------------------------------------------------------
// Function for creating a matrix for scaling a object.
//	x (float): how many times bigger in x?
//	y (float): how many times bigger in y?
//	z (float): how many times bigger in z?
//	Formula: [x  0  0  0]
//			 [0  y  0  0]
//			 [0  0  z  0]
//			 [0  0  0  1]
//-----------------------------------------------------------
	void setScaled(float x, float y, float z)
	{
		xAxis = { x, 0, 0, 0 };
		yAxis = { 0, y, 0, 0 };
		zAxis = { 0, 0, z, 0 };
		wAxis = { 0, 0, 0, 1 };
	}
//-----------------------------------------------------------
// Function for scaling a object.
//	x (float): how many times bigger in x?
//	y (float): how many times bigger in y?
//	z (float): how many times bigger in z?
//-----------------------------------------------------------
	void scale(float x, float y, float z)
	{
		Mat4<T> m;
		m.setScaled(x, y, z);
		*this = *this * m;
	}
//-----------------------------------------------------------
// Function for creating a matrix for translating a object.
//	x (float): how much in x direction?
//	y (float): how much in y direction?
//	y (float): how much in z direction?
//	Formula: [1  0  0  0]
//			 [0  1  0  0]
//			 [0  0  1  0]
//			 [x  y  z  1]
//-----------------------------------------------------------
	void setTranslate(float x, float y, float z)
	{
		xAxis = { 1, 0, 0, 0 };
		yAxis = { 0, 1, 0, 0 };
		zAxis = { 0, 0, 1, 0 };
		wAxis = { x, y, z, 1 };
	}
//-----------------------------------------------------------
// Function for translating a object.
//	x (float): how many times bigger in x?
//	y (float): how many times bigger in y?
//	z (float): how many times bigger in y?
//-----------------------------------------------------------
	void translate(float x, float y, float z)
	{
		Mat4<T> m;
		m.setTranslate(x, y, z);
		*this = *this * m;
	}
};