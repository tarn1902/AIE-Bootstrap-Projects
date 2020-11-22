/*----------------------------------------
File Name: FuzzyLogicEngine.h
Purpose: Runs Fuzzy Logic system
Author: Tarn Cooper
Modified: 07 June 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "FuzzyLogicEngine.h"

//-----------------------------------------------------------
// Creates right shoulder membership function
// x0 (float): Where is point 0 on x axis?
// x1 (float): Where is point 1 on x axis?
// name (string): What is this functions purpose?
//-----------------------------------------------------------
rightShoulderMembershipFunction::rightShoulderMembershipFunction(float x0,float x1,string name)
{
	_x0 = x0;
	_x1 = x1;
	_name = name;
}

//-----------------------------------------------------------
// Gets membership of point based on graph
// x (float): What point on graph?
// return (float): Returns value between one and zero based
// on membership on graph
//-----------------------------------------------------------
float rightShoulderMembershipFunction::getMembership(float x)
{
	float result = 0;
	if(x <= _x0)
		result = 0;
	else if(x >= _x1)
		result = 1;
    else
		result = (x/(_x1-_x0))-(_x0/(_x1-_x0));
	return result;
}

//-----------------------------------------------------------
// Gets max membership based on graph
// return (float): Returns max membership on graph for 
// defuzzifying
//-----------------------------------------------------------
float rightShoulderMembershipFunction::getMaxMembership()
{
	return (_x1+1)*.5f;
}

//-----------------------------------------------------------
// Creates left shoulder membership function
// x0 (float): Where is point 0 on x axis?
// x1 (float): Where is point 1 on x axis?
// name (string): What is this functions purpose?
//-----------------------------------------------------------
leftShoulderMembershipFunction::leftShoulderMembershipFunction(float x0,float x1,string name)
{
	_x0 = x0;
	_x1 = x1;
	_name = name;
}

//-----------------------------------------------------------
// Gets membership of point based on graph
// x (float): What point on graph?
// return (float): Returns value between one and zero based
// on membership on graph
//-----------------------------------------------------------
float leftShoulderMembershipFunction::getMembership(float x)
{
	float result = 0;
	if(x <= _x0)
		result = 1;
	else if(x >= _x1)
		result = 0;
    else
		result = (-x/(_x1-_x0))+(_x1/(_x1-_x0));
	return result;
}

//-----------------------------------------------------------
// Gets max membership based on graph
// return (float): Returns max membership on graph for 
// defuzzifying
//-----------------------------------------------------------
float leftShoulderMembershipFunction::getMaxMembership()
{
	return (_x0)*.5f;
}

//-----------------------------------------------------------
// Creates triangle membership function
// x0 (float): Where is point 0 on x axis?
// x1 (float): Where is point 1 on x axis?
// x2 (float): Where is point 2 on x axis?
// name (string): What is this functions purpose?
//-----------------------------------------------------------
TriangleFunction::TriangleFunction(float x0,float x1,float x2,string name)
{
	_x0 = x0;
	_x1 = x1;
	_x2 = x2;
	_name = name;
}

//-----------------------------------------------------------
// Gets membership of point based on graph
// x (float): What point on graph?
// return (float): Returns value between one and zero based
// on membership on graph
//-----------------------------------------------------------
float TriangleFunction::getMembership(float x)
{
	float result = 0;
	if(x <= _x0 || x >= _x2)
		result = 0;
	else if(x == _x1)
		result = 1;
	else if((x>_x0) && (x<_x1))
		result = (x/(_x1-_x0))-(_x0/(_x1-_x0));
	else
		result = (-x/(_x2-_x1))+(_x2/(_x2-_x1));
	return result;
}

//-----------------------------------------------------------
// Gets max membership based on graph
// return (float): Returns max membership on graph for 
// defuzzifying
//-----------------------------------------------------------
float TriangleFunction::getMaxMembership()
{
	return _x1;
}

//-----------------------------------------------------------
// Creates trapezoid membership function
// x0 (float): Where is point 0 on x axis?
// x1 (float): Where is point 1 on x axis?
// x2 (float): Where is point 2 on x axis?
// x3 (float): Where is point 3 on x axis?
// name (string): What is this functions purpose?
//-----------------------------------------------------------
TrapezoidFunction::TrapezoidFunction(float x0,float x1,float x2,float x3,string name)
{
	_x0 = x0;
	_x1 = x1;
	_x2 = x2;
	_x3 = x3;
	_name = name;
}

//-----------------------------------------------------------
// Gets membership of point based on graph
// x (float): What point on graph?
// return (float): Returns value between one and zero based
// on membership on graph
//-----------------------------------------------------------
float TrapezoidFunction::getMaxMembership()
{
	return (_x1+_x2)*.5f;
}

//-----------------------------------------------------------
// Gets max membership based on graph
// return (float): Returns max membership on graph for 
// defuzzifying
//-----------------------------------------------------------
float TrapezoidFunction::getMembership(float x)
{
	float result = 0;
	if(x <= _x0 || x >= _x3)
		result = 0;
	else if((x>=_x1) && (x<=_x2))
		result = 1;
	else if((x>_x0) && (x<_x1))
		result = (x/(_x1-_x0))-(_x0/(_x1-_x0));
	else
		result = (-x/(_x3-_x2))+(_x3/(_x3-_x2));
	return result;
}

//-----------------------------------------------------------
// Gets lower value of two desires
// f1 (float): What is first desire
// f2 (float): What is second desire
// return (float): Returns lower value
//-----------------------------------------------------------
float Fuzzy::AND(float f1,float f2)
{
	if(f1<f2)
	{
		return f1;
	}
	else
	{
		return f2;
	}
}

//-----------------------------------------------------------
// Gets higher value of two desires
// f1 (float): What is first desire
// f2 (float): What is second desire
// return (float): Returns higher value
//-----------------------------------------------------------
float Fuzzy::OR(float f1,float f2)
{
	if(f1>f2)
	{
		return f1;
	}
	else
	{
		return f2;
	}
}

//-----------------------------------------------------------
// Gets opposite value of desire
// f1 (float): What is desire
// return (float): Returns opposite value for desire
//-----------------------------------------------------------
float Fuzzy::NOT(float f1)
{
	return 1 - f1;
}