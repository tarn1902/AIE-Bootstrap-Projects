/*----------------------------------------
File Name: main.cpp
Purpose: Function that starts program
Author: Tarn Cooper
Modified: 25 May 2020
------------------------------------------
Copyright 2020 Tarn Cooper.
-----------------------------------*/
#include "SoundProgramming.h"
//-----------------------------------------------------------
// main function
//-----------------------------------------------------------
int main() {
	
	auto app = new SoundProgramming();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}