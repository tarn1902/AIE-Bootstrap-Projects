/*------------------------------------------------
	File Name: main.cpp
	Purpose: Allows user to choose game to play
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/

#include <iostream>
using namespace std;

//Prototypes for game functions
void RunBinaryExercise();
void PlayGuessingGame();
void WatchBattleArena();
void PlayTicTacToeGame();

int main()
{
	int choice = -1;
	//Runs till user chooses to exit
	while (choice != 0)
	{
		system("CLS");
		cout << "What game would you like to play?" << endl
			<< "(Tic Tac Toe Game [1], Battle Arena Game [2], Guessing Game [3], Binary Exercise [4], Exit [0])" << endl
			<< "Game: ";
		cin >> choice;
		//Loops till valid input is inserted
		while (!cin.good())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Please enter number that corresponds to above list." << endl 
				<< "Game: ";
			cin >> choice;
		}
		//Uses valid input to start game
		switch (choice)
		{
		case 0:
			break;
		case 1:
			PlayTicTacToeGame();
			break;
		case 2:
			WatchBattleArena();
			break;
		case 3:
			PlayGuessingGame();
			break;
		case 4:
			RunBinaryExercise();
			break;
		//If outside range of choices, gives error
		default:
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Please enter number that corresponds to above list." << endl
				<< "Game: ";
			break;
		}
	}
	return 0;
}