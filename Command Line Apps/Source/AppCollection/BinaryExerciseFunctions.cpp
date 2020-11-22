/*------------------------------------------------
	File Name: BinaryExerciseFunctions.cpp
	Purpose: Holds functions called by
			TicTacToeGame.cpp
	Author: Tarn Cooper
	Modified: 04 March 2019
---------------------------------------------------
	Copyright 2019 Tarn Cooper
-------------------------------------------------*/
#include "Record.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
//--------------------------------------------
//Writes a binary file based on struct
//	libraryArray (Record[]): function turns
//								this into 
//								binary file
//	arraySize (int ): used to limit loop
//	return (bool) : checks if it worked
//---------------------------------------------
bool WriteBinary(Record libraryArray[], int arraySize)
{
	ofstream fout("library.dat", ios::out | ios::binary);
	if (fout.good()) {
		for (int i = 0; i < arraySize; i++) {
			fout.write((char*)&libraryArray[i], sizeof(Record));
		}
		fout.close();
		return true;
	}
	return false;
}

//--------------------------------------------
//Reads a binary file and puts in array
//	libraryArray (Record[]): function converts 
//							binary file into
//							this
//								
//	arraySize (int ): used to limit loop
//	return (bool) : checks if it worked
//---------------------------------------------
bool ReadBinary(Record libraryArray[], int arraySize)
{
	ifstream fin("library.dat", ios::in | ios::binary);
	if (fin.good())
	{
		for (int i = 0; i < arraySize; i++)
		{
			fin.read((char*)&libraryArray[i], sizeof(Record));
		}
		fin.close();
		return true;
	}
	return false;
}

//--------------------------------------------
//Reads a binary file and puts in array
//	libraryArray (Record[]): function converts 
//							binary file into
//							this
//								
//	arraySize (int ): used to limit loop
//	return (bool) : checks if it worked
//---------------------------------------------
bool ReadText(Record libraryArray[], int arraySize)
{
	ifstream fin("library.txt", ios::in);
	string temp;
	if (fin.good())
	{
		for (int i = 0; i < arraySize; i++)
		{
			getline(fin, temp);
			strcpy_s(libraryArray[i].callNumber, temp.c_str());
			getline(fin, temp);
			strcpy_s(libraryArray[i].title, temp.c_str());
			getline(fin, temp);
			strcpy_s(libraryArray[i].author, temp.c_str());
			getline(fin, temp);
			strcpy_s(libraryArray[i].bookStatus, temp.c_str());

			//Tests if borrowed
			if (strcmp("2", libraryArray[i].bookStatus) == 0)
			{
				getline(fin, temp);
				strcpy_s(libraryArray[i].dueDate, temp.c_str());
				getline(fin, temp);
				strcpy_s(libraryArray[i].borrowerName, temp.c_str());
			}
			else
			{
				strcpy_s(libraryArray[i].dueDate, "");
				strcpy_s(libraryArray[i].borrowerName, "");
				continue;
			}
		}
		fin.close();
		return true;
	}
	return false;
}

//--------------------------------------------
//Uses array to find certain records
//	lookNumber (char*): checks if number is in 
//						records
//	libraryArray (Record[]): checks look number
//								in this
//								
//	arraySize (int ): used to limit loop
//	return (int) : position in array of file if 
//					found
//---------------------------------------------
int FindRecord(char* lookNumber, Record libraryArray[], int arraySize)
{
	for (int i = 0; i < arraySize; i++)
	{

		if (strcmp(lookNumber, libraryArray[i].callNumber) == 0)
		{
			return i;
		}
	}
	return -1;
}

//---------------------------------------------
//Displays record on console
//	findNumber (int): used specify which 
//						record
//	libraryArray (Record[]): searches and gets
//								info from array
//----------------------------------------------
void DisplayRecord(int findNumber, Record libraryArray[])
{
	cout << "Call Number: " << libraryArray[findNumber].callNumber << endl << "Title: " << libraryArray[findNumber].title << endl << "Author: " << libraryArray[findNumber].author << endl << "Book Status: " << libraryArray[findNumber].bookStatus << endl;
	if (strcmp("2", libraryArray[findNumber].bookStatus) == 0)
	{
		cout << "Due Date: " << libraryArray[findNumber].dueDate << endl << "Borrower Name: " << libraryArray[findNumber].borrowerName << endl;
	}
}

//---------------------------------------------
//Reads maximum array of binary file
//return (int): returns the maximum of array
//----------------------------------------------
int ReadMaxArray()
{
	ifstream fin("maxArray.txt", ios::in);
	string temp;
	if (fin.good())
	{
		getline(fin, temp);

		fin.close();
		return stoi(temp);
	}
	fin.close();
	return -1;
}

//---------------------------------------------
//Reads maximum array of binary file
//oldMaxArray (int): Gives previus maximum of array
//----------------------------------------------
void WriteMaxArray(int oldMaxArray)
{
	ofstream fout("maxArray.txt", ios::out);
	int newMaxArray = oldMaxArray + 1;
	fout << newMaxArray;
	fout.close();
}

//---------------------------------------------
//Updates record in array
//	findNumber (int): used specify which 
//						record
//	libraryArray (Record[]): searches and changes
//								info in array
//----------------------------------------------
void UpdateRecord(int findNumber, Record libraryArray[])
{
	string temp = "";
	cout << "Call Number: ";
	getline(cin, temp);
	//If nothing is added it will use default
	if (!temp.empty())
	{
		//Copys string to char array
		strcpy_s(libraryArray[findNumber].callNumber, temp.c_str());
	}
	cout << "Title: ";
	getline(cin, temp);
	if (!temp.empty())
	{
		strcpy_s(libraryArray[findNumber].title, temp.c_str());
	}
	cout << "Author: ";
	getline(cin, temp);
	if (!temp.empty())
	{
		strcpy_s(libraryArray[findNumber].author, temp.c_str());
	}
	cout << "Book Status: ";
	getline(cin, temp);
	if (!temp.empty())
	{
		strcpy_s(libraryArray[findNumber].bookStatus, temp.c_str());
	}

	//Tests if borrowed
	if (strcmp(libraryArray[findNumber].bookStatus, "2") == 0)
	{
		cout << "Due Date: ";
		getline(cin, temp);
		if (!temp.empty())
		{
			strcpy_s(libraryArray[findNumber].dueDate, temp.c_str());
		}
		cout << "BorrowerName: ";
		getline(cin, temp);
		if (!temp.empty())
		{
			strcpy_s(libraryArray[findNumber].borrowerName, temp.c_str());
		}
	}
	else
	{
		strcpy_s(libraryArray[findNumber].dueDate, "");
		strcpy_s(libraryArray[findNumber].borrowerName, "");
	}
}

//---------------------------------------------
//Adds new record to array
//	libraryArray (Record[]): searches and changes
//								info in array
//	arraySize (int): used to limit loop
//----------------------------------------------
void AddRecord(Record libraryArray[], int arraySize)
{
	UpdateRecord(arraySize-1, libraryArray);
	WriteMaxArray(arraySize);
}

