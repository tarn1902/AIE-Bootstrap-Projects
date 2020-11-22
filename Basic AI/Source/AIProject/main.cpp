/*----------------------------------------
File Name: main.cpp
Purpose: runs program
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "AIProjectApp.h"

//first thing to run in program
int main() {
	
	// allocation
	auto app = new AIProjectApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}