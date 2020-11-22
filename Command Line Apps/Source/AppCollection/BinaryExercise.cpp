/*------------------------------------------------
	File Name: BinaryExercise.cpp
	Purpose: Exercise using read and writing of
			binary and text
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>
#include "Record.h"
using namespace std;

//Prototypes for functions
bool WriteBinary(Record[], int);
bool ReadBinary(Record[], int);
bool ReadText(Record[], int);
int FindRecord(char*, Record[], int);
void DisplayRecord(int, Record[]);
void UpdateRecord(int, Record[]);
void AddRecord(Record[], int);
int ReadMaxArray();



//Main function for running Binary Exercise
void RunBinaryExercise()
{
	bool isRunning = true;
	//Instructions for game
	system("CLS");
	cout << "This is a Binary Conversion application." << endl
		<< "This a program that turns records into binary and back" << endl
		<< "This example is based on book keeping" << endl
		<< "This exercise includes function that allows user to change the binary file" << endl
		<< "Anthing put in here will remain till manual deletion" << endl;
	system("Pause");
	system("CLS");
	int maxArray = ReadMaxArray();
	if (maxArray == -1)
	{
		cout << "Error: maxArray.txt could not be read...";
		system("pause");
		isRunning = false;
		return;

	}
	int findNumber = -1;
	Record* libraryArray = new Record[maxArray];

	//Checks if text or binery file is found and used
	if (!ReadBinary(libraryArray, maxArray))
	{
		if (!ReadText(libraryArray, maxArray))
		{
			cout << "Error: Text file not found" << endl;
			isRunning = false;
			return;

		}
		else
		{
			WriteBinary(libraryArray, maxArray);
		}
	}

	while (isRunning)
	{
		char command;
		char lookNumber[10];
		
		//Gets input and makes decision
		cout << "(f = find record, d = display record, e = exit program, u = update record, a = add record)" << endl
			<< "Command: ";
		cin >> command;
		cin.ignore();
		cin.clear();

		//Uses character to trigger command
		switch (command)
		{
		//Used to find number user wnats to select
		case 'f':
		{
			cout << "Call Number: ";
			cin >> lookNumber;
			findNumber = FindRecord(lookNumber, libraryArray, maxArray);
			if (findNumber == -1)
			{
				cout << "Error: Call Number not found" << endl;
			}
			else
			{
				cout << "Call Number found..." << endl;
			}
			break;
		}
		//Used to display selected numbers info
		case 'd':
		{
			if (findNumber == -1)
			{
				cout << "Error: Call Number has not been selected" << endl;
			}
			else
			{
				cout << "Displaying record..." << endl;
				DisplayRecord(findNumber, libraryArray);
			}
			break;
		}
		//Used to exit program
		case 'e':
		{
			delete[] libraryArray;
			cout << "Program closing..." << endl;
			isRunning = false;
			break;
		}

		//Used to update record
		case 'u':
		{
			cout << "Updating record..." << endl;
			UpdateRecord(findNumber, libraryArray);
			WriteBinary(libraryArray, maxArray);
			break;
		}

		//Used to add record
		case 'a':
		{
			cout << "Adding record..." << maxArray << endl;
			AddRecord(libraryArray, maxArray);
			WriteBinary(libraryArray, maxArray);
			delete[] libraryArray;
			maxArray = ReadMaxArray();
			Record* libraryArray = new Record[maxArray];
			ReadBinary(libraryArray, maxArray);
			break;
			
		}

		//Gives Error message
		default:
		{
			cout << "Error: Invalid input" << endl;
			break;
		}
		}
	}
	system("Pause");
}

