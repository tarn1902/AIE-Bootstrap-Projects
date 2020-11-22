/*------------------------------------------------
	File Name: BattleArenaFunctions.cpp
	Purpose: Holds functions called by 
			BattleArena.cpp
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#include "Fighter.h"
#include <iostream>

//--------------------------------------------
//Tests if any survivors on team
//	victims (Fighter[]): Gets health info from
//						array to see who alive
//	return (bool): Returns if defeated or not
//---------------------------------------------
bool Defeated(Fighter victims[], int maxArray)
{
	int defeated = 0;
	for (int i = 0; i < maxArray; i++)
	{
		if (victims[i].getHealth() <= 0)
		{
			defeated++;
		}
	}
	if (defeated == maxArray)
	{
		return true;
	}
	return false;
}
//--------------------------------------------
//prints out roster of fighters
//	team1 (Fighter[]): Gets all fighters in  
//						team 1 to display
//	team2 (Fighter[]): Gets all fighters in  
//						team 2 to display
//---------------------------------------------
void BuildRoster(Fighter team1[], Fighter team2[], int maxArray)
{
	system("CLS");
	cout << "Team Iron Man: " << endl;
	for (int i = 0; i < maxArray; i++)
	{
		cout << team1[i].getName() << " (" << team1[i].getHealth() << ")	" << endl;
	}
	cout << endl;

	cout << "Team Captain America: " << endl;
	for (int i = 0; i < maxArray; i++)
	{
		cout << team2[i].getName() << " (" << team2[i].getHealth() << ")	" << endl;
	}
	cout << endl;
}

//--------------------------------------------
//Sorts team array from most health to least
//	team (Fighter[]): Gets and sorts fighters
//						in this array
//---------------------------------------------
void Sort(Fighter team[], int maxArray)
{
	int length = maxArray;
	if (maxArray < 2)
	{
		return;
	}
	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (int i = 0; i < length; i++)
		{
			if (team[i].getHealth() < team[i + 1].getHealth())
			{
				swap(team[i], team[i + 1]);
				sorted = false;
				length--;
			}
		}
	}
}

//--------------------------------------------
//Lets a fighter attacker random member of other
//	team
//	attacker (Fighter): Gets attacking info from
//						fighter
//	victims (Fighter): Gets random victim from 
//						array and uses health
//						info
//	return (bool): Returns if victims have been 
//					defeated
//---------------------------------------------
void Attack(Fighter attacker, Fighter victims[], int maxArray)
{
	int target;
	int damage;

	if (!(attacker.getHealth() <= 0))
	{
		target = rand() % maxArray;
		while (victims[target].getHealth() <= 0)
		{
			target = rand() % maxArray;
		}
		damage = rand() % attacker.getAttack();
		victims[target].setHealth(victims[target].getHealth() - damage);
		cout << attacker.getName() << " " << attacker.getAttackName() << " " << victims[target].getName() << " for " << damage << " points of damage. ";
		if (victims[target].getHealth() <= 0)
		{
			cout << victims[target].getName() << " was defeated.";
			victims[target].setHealth(0);
		}
		cout << endl;
		system("Pause");
	}
}