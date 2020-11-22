/*----------------------------------------
File Name: main.cpp
Purpose: Starts Application
Author: Tarn Cooper
Modified: 08 March 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "PhysicsEngineApp.h"
//-----------------------------------------------------------
// First function to run in program
// return (int): return 0 if runs correctly
//-----------------------------------------------------------
int main() {
	
	// allocation
	auto app = new PhysicsEngineApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}