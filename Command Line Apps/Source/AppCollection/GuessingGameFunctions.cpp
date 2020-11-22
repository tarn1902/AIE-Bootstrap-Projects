/*------------------------------------------------
	File Name: GuessingGameFunctions.cpp
	Purpose: Holds functions called by 
			GuessingGame.cpp
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#include <iostream>
using namespace std;
//--------------------------------------------
//Uses hint for Binary Search to find answer
//	hint (char): Uses hint to make decision
//	min (&int): used for minimum value it 
//				could be
//	max (&int): used for maximum value it 
//				could be
//	center (&center): used as center of array 
//				and as guess
//	count (&int): used to count loops
//	return (bool): if game is ended
//---------------------------------------------
bool Check(char hint, int &min, int &max, int &center, int &count)
{
	switch (hint)
	{
	case '=':
	{
		count++;
		cout << "Yay. I guessed it in " << count << " tries!";
		return true;
	}
	case '<':
	{
		//calculates new min value
		min = center + 1;

		count++;
		break;
	}
	case'>':
	{
		//calculates new max value
		max = center - 1;

		count++;
		break;
	}
	default:
	{
		cout << "Error: Please use diffrent symbol." << endl;
		break;
	}
	}
	//Test if guess is not in range
	if (min > max)
	{
		cout << "Error: Your number was not in the range." << endl;
		return true;
	}
	////calculates new center value
	center = (min + max) / 2;
	return false;
}