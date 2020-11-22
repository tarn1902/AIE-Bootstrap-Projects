/*----------------------------------------
File Name: Stack.h
Purpose: Controls how the Stack behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "LinkList.h"
template <typename T>
//-----------------------------------------------------------
// Object for controling a stack
//-----------------------------------------------------------
class Stack
{
public:
//-----------------------------------------------------------
// Contructs this object
//-----------------------------------------------------------
	Stack()
	{

	}
//-----------------------------------------------------------
// Destroys this object
//-----------------------------------------------------------
	~Stack()
	{

	}
//-----------------------------------------------------------
// Removes value from list
//-----------------------------------------------------------
	void Pop()
	{
		list.PopBack();
	}

//-----------------------------------------------------------
// Gets number of values in list
//-----------------------------------------------------------
	int Count()
	{
		return list.Count();
	}

//-----------------------------------------------------------
// Adds value to list
//	value (T): What value is inserted into list?
//-----------------------------------------------------------
	void Push(T value)
	{
		list.PushBack(value);
	}

	LinkedList<T> list;
};