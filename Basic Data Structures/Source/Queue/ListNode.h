/*----------------------------------------
File Name: ListNode.h
Purpose: Holds data of each List Node
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
template <typename T>
//-----------------------------------------------------------
// Object for holding data
//-----------------------------------------------------------
struct ListNode
{
	T data;
	ListNode<T>* next = nullptr;
};
