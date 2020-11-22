/*----------------------------------------
File Name: Player.cpp
Purpose: Holds each method for Player.h
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "Player.h"


//-----------------------------------------------------------
// Contructs this object
//-----------------------------------------------------------
Player::Player()
{
	points = 0;
}

//-----------------------------------------------------------
// Destroys this object
//-----------------------------------------------------------
Player::~Player()
{
}

//-----------------------------------------------------------
// Sets Points of player
//	inPoints (int): How many points does player have?
//-----------------------------------------------------------
void Player::SetPoints(int inPoints)
{
	points = inPoints;
}

//-----------------------------------------------------------
// Gets Points of player
//	return (int): returns points player has.
//-----------------------------------------------------------
int Player::GetPoints()
{
	return points;
}