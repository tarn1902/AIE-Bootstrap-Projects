/*----------------------------------------
File Name: main.cpp
Purpose: Starts application
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "QueueApp.h"

//-----------------------------------------------------------
// First method that runs when program starts
//-----------------------------------------------------------
int main() {
	
	// allocation
	auto app = new QueueApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}