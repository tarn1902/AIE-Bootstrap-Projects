/*------------------------------------------------
	File Name: Fighter.h
	Purpose: Holds header information for fighter
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#pragma once
#include <string>
using namespace std;

class Fighter
{
public:
	Fighter();
	Fighter(string, string, int, int);
	~Fighter();

	void setHealth(int inHealth)
	{
		health = inHealth;
	}

	int getHealth()
	{
		return health;
	}

	int getAttack()
	{
		return attack;
	}

	string getName()
	{
		return name;
	}

	string getAttackName()
	{
		return attackName;
	}

private:
	int health;
	int attack;
	string name;
	string attackName;
};

