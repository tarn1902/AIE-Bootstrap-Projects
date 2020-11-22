/*----------------------------------------
File Name: Utilities.h
Purpose: Handy tools used in this project
Author: Tarn Cooper
Modified: 16/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
//-----------------------------------------------------------
// Function for getting minimum of two floats
// a(float): What is number a?
// b (float) What is number b?
// return (float): returns smaller number
//-----------------------------------------------------------
inline float minf(float a, float b) { return a < b ? a : b; }
//-----------------------------------------------------------
// Function for getting  of two floats
// a(float): What is number a?
// b (float) What is number b?
// return (float): returns larger number
//-----------------------------------------------------------
inline float maxf(float a, float b) { return a > b ? a : b; }
//-----------------------------------------------------------
// Function for getting minimum of two Vector2
// a(Vec2<float>): What is vector2 a?
// b (Vec2<float>) What is vector2 b?
// return (Vec2<float>): returns smaller vector2
//-----------------------------------------------------------
inline Vec2<float> min(const Vec2<float>& a, const Vec2<float>& b)
{
	return { minf(a.x,b.x), minf(a.y, b.y) };
}
//-----------------------------------------------------------
// Function for getting maximum of two Vector2
// a(Vec2<float>): What is vector2 a?
// b (Vec2<float>) What is vector2 b?
// return (Vec2<float>): returns larger vector2
//-----------------------------------------------------------
inline Vec2<float> max(const Vec2<float>& a, const Vec2<float>& b)
{
	return { maxf(a.x,b.x), maxf(a.y, b.y) };
}
//-----------------------------------------------------------
// Function for keeping vector between to vectors
// t(const Vec2<float>&): What vector2 to be clamped
// a(const Vec2<float>&): What is min vector2?
// b (const Vec2<float>&) What is max vector2 b?
// return (Vec2<float>): returns t clamped
//-----------------------------------------------------------
inline Vec2<float> clamp(const Vec2<float>& t, const Vec2<float>& a, const Vec2<float>& b)
{
	return max(a, min(b, t));
}
//-----------------------------------------------------------
// Function for getting minimum of two floats
// a(float): What is number a?
// b (float) What is number b?
// return (float): returns smaller number
//-----------------------------------------------------------
inline float min(float a, float b)
{
	return { minf(a, b) };
}
//-----------------------------------------------------------
// Function for getting  of two floats
// a(float): What is number a?
// b (float) What is number b?
// return (float): returns larger number
//-----------------------------------------------------------
inline float max(float a, float b)
{
	return { maxf(a, b) };
}

//-----------------------------------------------------------
// Function for clamping two floats
// t (float) What is number to be clamped?
// a(float): What is min number?
// b (float) What is max number?
// return (float): returns t clamped
//-----------------------------------------------------------
inline float clamp(float t, float a, float b)
{
	return max(a, min(b, t));
}