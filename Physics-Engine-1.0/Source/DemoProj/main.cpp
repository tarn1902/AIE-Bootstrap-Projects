/*----------------------------------------
File Name: main.cpp
Purpose: Runs within visual studio
Author: Tarn Cooper
Modified: 16/06/2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "DemoProjApp.h"
//-----------------------------------------------------------
// First thing to run
// returns (int*): returns 0 if successful
//-----------------------------------------------------------
int main() {
	
	// allocation
	auto app = new DemoProjApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}