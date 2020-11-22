/*------------------------------------------------
	File Name: TicTacToeGameFunctions.cpp
	Purpose: Holds functions called by 
			TicTacToeGame.cpp
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#include <iostream>
using namespace std;
//--------------------------------------------
//prints out board for player to reference
//	board (char[3][3]): Gets current values in 
//						the array
//---------------------------------------------
void BuildBoard(char board[3][3])
{
	//loops through array and creates board with content wraped in brackets
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			cout << "[" << board[i][j] << "]";
		}
		cout << endl;
	}
}