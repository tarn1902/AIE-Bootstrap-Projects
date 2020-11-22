/*------------------------------------------------
	File Name: main.cpp
	Purpose: A text based battle simulator
			 (Avengers: Civil War)
	Author: Tarn Cooper
	Modified: 25 February 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#include <iostream>
#include <ctime>
#include <string>
#include "Fighter.h"

using namespace std;

void Sort(Fighter[], int);
void Attack(Fighter, Fighter[], int);
bool Defeated(Fighter[], int);
void BuildRoster(Fighter[], Fighter[], int);

//Main function for Battle Arena
void WatchBattleArena()
{
	//Instructions for game
	system("CLS");
	cout << "This is battle." << endl
		<< "This is based on civil war." << endl
		<< "You watch as team iron man and team captain america fight till one side is defeated." << endl
		<< "Arena end once all member of a team are down." << endl
		<< "May the best team win.";
	system("Pause");
	system("CLS");

	//Create each Fighter
	Fighter ironMan = Fighter("Iron Man", "Beamed", 100, 100);
	Fighter warMachine = Fighter("War Machine", "Rocketed", 100, 100);
	Fighter captainAmerica = Fighter("Captain America", "Shield Hit", 100, 100);
	Fighter buckyBarnes = Fighter("Bucky Barnes", "Metal Punched", 100, 100);
	Fighter blackWidow = Fighter("Black Widow", "Kicks", 100, 100);
	Fighter hawkEye = Fighter("Hawkeye", "Shot", 100, 100);
	Fighter blackPanther = Fighter("Black Panther", "Punched", 100, 100);
	Fighter falcon = Fighter("Falcon", "Shot", 100, 100);
	Fighter theVision = Fighter("The Vision", "Punched", 100, 100);
	Fighter antMan = Fighter("Ant-Man", "Punched", 100, 100);
	Fighter spiderMan = Fighter("Spider-Man", "Webbed", 100, 100);
	Fighter scarletWitch = Fighter("Scarlet Witch", "Manipulated", 100, 100);

	//Creates each team using fighters
	
	
	bool isRunning = true;
	bool isPlaying = true;
	char choice;
	char inMaxArray;
	int outMaxArray;

	srand((unsigned int)time(NULL));

	while (isRunning)
	{
		//Asks how big the battle will be
		cout << "How many people will fight? (0 - 6)";
		cin >> inMaxArray;
		while (!isdigit(inMaxArray) || (int)inMaxArray-48 >= 7 || (int)inMaxArray - 48 <= 0)
		{
			cout << "Error: Invalid input." << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			cout << "How many people will fight?";
			cin >> inMaxArray;
		}
		outMaxArray = (int)inMaxArray - 48;

		//Creates new array for fighters
		Fighter* team1 = new Fighter[outMaxArray];
		Fighter* team2 = new Fighter[outMaxArray];

		//adds members to it
		switch (outMaxArray)
		{
		default:
		{
			team2[5] = scarletWitch;
			team1[5] = spiderMan;
		}
		case '5':
		{
			team2[4] = antMan;
			team1[4] = theVision;
		}
		case '4':
		{
			team2[3] = falcon;
			team1[3] = blackPanther;
		}
		case '3':
		{
			team2[2] = hawkEye;
			team1[2] = blackWidow;
		}
		case '2':
		{
			team2[1] = buckyBarnes;
			team1[1] = warMachine;
		}
		case '1':
		{
			team2[0] = captainAmerica;
			team1[0] = ironMan;
		}
		}
		
		while(isPlaying)
		{
		//This loops through each of the team arrays
			for (int i = 0; i < outMaxArray; i++)
			{
				//This goes through array so each fighter on team attackers
				if (isPlaying)
				{
					BuildRoster(team1, team2, outMaxArray);
					Attack(team1[i], team2, outMaxArray);
					Sort(team2, outMaxArray);

					if (Defeated(team2, outMaxArray))
					{
						BuildRoster(team1, team2, outMaxArray);
						cout << "Team Iron Man Wins" << endl;
						isPlaying = false;
						system("Pause");
					}

				}
				Sort(team2, outMaxArray);
				//This goes through array so each fighter on other team attackers
				if (isPlaying)
				{
					BuildRoster(team1, team2, outMaxArray);
					Attack(team2[i], team1, outMaxArray);
					Sort(team1, outMaxArray);


					if (Defeated(team1, outMaxArray))
					{
						BuildRoster(team1, team2, outMaxArray);
						cout << "Team Captain America Wins" << endl;
						isPlaying = false;
						system("Pause");
					}
				}
				Sort(team1, outMaxArray);
			}
		}
		//Asks if want to play again
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

		//Deletes team array

		delete [] team1;
		delete [] team2;

		//Ends Program
		if (choice == '2')
		{
			isRunning = false;
		}

		//Resets game
		else
		{
			isPlaying = true;
		}
	}
}