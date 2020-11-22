/*----------------------------------------
File Name: main.cpp
Purpose: Runs app
Author: Tarn Cooper
Modified: 07 June 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "Complex_FuzzyLogicApp.h"

//-----------------------------------------------------------
// Runs app
// returns (int): returns value depending on ending result
//-----------------------------------------------------------
int main() {
	
	auto app = new Complex_FuzzyLogicApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}