/*------------------------------------------------
	File Name: Fighter.cpp
	Purpose: Holds class Fighter called by 
			BattleArena.cpp
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#include "Fighter.h"
#include <string>
using namespace std;

//Constructor of Fighter
Fighter::Fighter(string inName, string inAttackName, int inHealth, int inAttack)
{
	name = inName;
	attackName = inAttackName;
	health = inHealth;
	attack = inAttack;

}

//Destructor of Fighter
Fighter::~Fighter()
{
}

//Default constructor of Fighter
Fighter::Fighter()
{
}
