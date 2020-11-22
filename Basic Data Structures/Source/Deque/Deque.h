/*----------------------------------------
File Name: Deque.h
Purpose: Controls how the deque behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "LinkList.h"
template <typename T>
//-----------------------------------------------------------
// Object for controling a deque
//-----------------------------------------------------------
class Deque
{
public:
//-----------------------------------------------------------
// Contructs this object
//-----------------------------------------------------------
	Deque()
	{

	}
//-----------------------------------------------------------
// Destroys this object
//-----------------------------------------------------------
	~Deque()
	{
		list.Clear();
	}

//-----------------------------------------------------------
// Removes value from front of list
//-----------------------------------------------------------
	void PopFront()
	{
		list.PopFront();
	}
//-----------------------------------------------------------
// Removes value from back of list
//-----------------------------------------------------------
	void PopBack()
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
// Adds value to back of list
//	value (T): What value is inserted to back of list?
//-----------------------------------------------------------
	void PushBack(T value)
	{
		list.PushBack(value);
	}

//-----------------------------------------------------------
// Adds value to front of list
//	value (T): What value is inserted to front of list?
//-----------------------------------------------------------
	void PushFront(T value)
	{
		list.PushFront(value);
	}

	LinkedList<T> list;
};
