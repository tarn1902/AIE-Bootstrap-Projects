/*----------------------------------------
File Name: main.cpp
Purpose: starts program
Author: Tarn Cooper
Modified: 04 August 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "DecisionBehaviourApp.h"

//Starts app
int main() {
	
	// allocation
	auto app = new DecisionBehaviourApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}