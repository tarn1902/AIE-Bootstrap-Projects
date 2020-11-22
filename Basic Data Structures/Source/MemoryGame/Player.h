/*----------------------------------------
File Name: Player.h
Purpose: Controls points for each player
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once

//-----------------------------------------------------------
// Object for holding points data
//-----------------------------------------------------------
class Player
{
public:
	Player();
	~Player();
	void SetPoints(int);
	int GetPoints();
private:
	int points;
};

