/*------------------------------------------------
	File Name: TicTacToeGame.cpp
	Purpose: A digital remake of TicTacToe
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#include <iostream>
using namespace std;

//Prototype for functions
void BuildBoard(char board[3][3]);

//Main function for Tic Tac Toe Game
void PlayTicTacToeGame()
{
	char board[3][3] = { {'7', '8', '9'}, {'4', '5', '6'} ,{'1', '2', '3'} };
	char pos = '0';
	char marker = 'X';
	bool isPlaying = true;
	bool isNotNum = false;
	bool isNotFound = false;
	bool isMarked = false;
	bool isRunning = true;
	int turn = 0;

	//Instructions for game
	system("CLS");
	cout << "This is Tic Tac Toe." << endl
		<< "This game is played between two players." << endl
		<< "Each player will take in turns to insert markers on board. " << endl
		<< "If player gets 3 in a row they win." << endl
		<< "If there are no winners and there is no where to go, it is a draw." << endl;
	system("Pause");
	system("CLS");
	while (isRunning)
	{
		char choice;
		while (isPlaying)
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			system("CLS");

			//Checks for Errors
			if (isNotNum)
			{
				cout << "Error: invalid input. Please use a interger between 1 - 9." << endl;
				isNotNum = false;
			}
			else if (isNotFound)
			{
				cout << "Error: invalid position. Please give a diffrent position." << endl;
				isNotFound = false;
			}
			else
			{
				cout << "Type the number that matches with position on table to place marker. " << endl;
			}

			//Displays Tic Tac Toe board
			BuildBoard(board);

			//Asks for position to place marker
			cout << "Player " << marker << "'s turn: ";
			cin >> pos;

			//Tests if not interger.
			if (!isdigit(pos))
			{
				isNotNum = true;
			}

			//Checks array for specfic position
			isNotFound = true;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					//Tests if position is taken
					if (pos == board[i][j])
					{
						board[i][j] = marker;
						isNotFound = false;
					}
				}
			}

			//Continues loop if error returns
			if (isNotFound || isNotNum)
			{
				system("CLS");
				continue;
			}

			//Test if same marker is used in a row and finishes game.
			if (board[0][0] == marker && board[0][1] == marker && board[0][2] == marker)
			{
				isPlaying = false;
			}
			else if (board[1][0] == marker && board[1][1] == marker && board[1][2] == marker)
			{
				isPlaying = false;
			}
			else if (board[2][0] == marker && board[2][1] == marker && board[2][2] == marker)
			{
				isPlaying = false;
			}

			//Test if same marker is used in a column and finishes game.
			if (board[0][0] == marker && board[1][0] == marker && board[2][0] == marker)
			{
				isPlaying = false;
			}
			else if (board[0][1] == marker && board[1][1] == marker && board[2][1] == marker)
			{
				isPlaying = false;
			}
			else if (board[0][2] == marker && board[1][2] == marker && board[2][2] == marker)
			{
				isPlaying = false;
			}

			//Test if same marker is used diagonaly and finishes game.
			if (board[0][0] == marker && board[1][1] == marker && board[2][2] == marker)
			{
				isPlaying = false;
			}
			else if (board[0][2] == marker && board[1][1] == marker && board[2][0] == marker)
			{
				isPlaying = false;
			}

			//Change marker each loop.
			if (isPlaying == true)
			{
				if (marker == 'X')
				{
					marker = 'O';
				}
				else if (marker == 'O')
				{
					marker = 'X';
				}
			}

			//If draw occured, finishes game
			if (++turn == 9)
			{
				isPlaying = false;
			}
		}

		system("CLS");
		cout << "The game is finished" << endl;

		BuildBoard(board);

		//If draw occured, prints out draw
		if (turn == 9)
		{
			cout << "It is a draw" << endl;
		}
		//Prints winner
		else
		{
			cout << "Winner is " << marker << endl;
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
			char newBoard[3][3] = { {'7', '8', '9'}, {'4', '5', '6'} ,{'1', '2', '3'} };
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					board[i][j] = newBoard[i][j];
				}
			}
			pos = '0';
			marker = 'X';
			isPlaying = true;
			turn = 0;
		}
	}
}