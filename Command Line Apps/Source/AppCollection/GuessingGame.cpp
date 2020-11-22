/*------------------------------------------------
	File Name: GuessingGame.cpp
	Purpose: Using binary to as effciently as 
			possible guess users number
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#include <iostream>
using namespace std;

const int MAX_ARRAY = 101;

bool Check(char, int &, int &, int &, int &);

//Main function for Guessing Game
void PlayGuessingGame()
{
	bool results = false;
	bool isRunning = true;
	int count = 0;
	int range[MAX_ARRAY];
	int min = 0;
	int max = MAX_ARRAY - 1;
	char hint;
	int num = (min + max) / 2;
	char choice;

	//Instructions for game
	system("CLS");
	cout << "This is Guessing Game." << endl
		<< "This game is played by one player" << endl
		<< "The computer will guess a number you are thinking between 0 - 100." << endl
		<< "You will need to give it a hint by using symbols of what number it could be " << endl
		<< "The computer will say how many times it guessed at the end" << endl
		<< "If you change the number or choose number outside, the computer will tell you" << endl;
	system("Pause");
	system("CLS");

	while (isRunning)
	{
		cout << "Pick a number between 0 - 100. Use symbols to give clues: (< (bigger), >(smaller), =(equal))" << endl;
		bool isPlaying = true;
		while (isPlaying)
		{
			//Fills array with numbers from 0 to 100
			for (int i = 0; i < MAX_ARRAY; i++)
			{
				range[i] = i;
			}

			//Loops till results are given
			while (!results)
			{
				cout << "Is your number: " << num << " ";
				cin >> hint;
				results = Check(hint, min, max, num, count);
			}
			isPlaying = false;
		}

		cout << "Do you want to play again? (1 = Yes, 2 = No): ";
		cin >> choice;
		while (!isdigit(choice) || choice != '2' && choice != '1')
		{
			cout << "Error: Invalid input." << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			cout << "Do you want to play again? (1 = Yes, 2 = No): ";
			cin >> choice;
		}

		//Ends Program
		if (choice == '2')
		{
			isRunning = false;
		}
		//Resets game
		else
		{
			system("CLS");
			results = false;
			count = 0;
			min = 0;
			max = MAX_ARRAY - 1;
			num = (min + max) / 2;
		}
	}
	system("Pause");
}

