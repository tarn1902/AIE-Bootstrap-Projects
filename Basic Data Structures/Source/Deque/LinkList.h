/*----------------------------------------
File Name: LinkList.h
Purpose: Controls how a linked list behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "ListNode.h"
template <typename T>
//-----------------------------------------------------------
// Object for controling a linked list
//-----------------------------------------------------------
class LinkedList
{
public:
//-----------------------------------------------------------
// Contructs this object
//-----------------------------------------------------------
	LinkedList()
	{

	}
//-----------------------------------------------------------
// Destroys this object
//-----------------------------------------------------------
	~LinkedList()
	{
		Clear();
	}

//-----------------------------------------------------------
// Inserts a value to front of linked list.
//	value (T): What value is inserted to front?
//-----------------------------------------------------------
	void PushFront(T value)
	{
		ListNode<T>* newNode = new ListNode<T>();
		newNode->next = head;
		newNode->data = value;
		head = newNode;
		count++;
		if (tail == nullptr)
		{
			tail = head;
		}
	}

//-----------------------------------------------------------
// Inserts a value to back of linked list.
//	value (T): What value is inserted to back?
//-----------------------------------------------------------
	void PushBack(T value)
	{
		ListNode<T>* newNode = new ListNode<T>();
		newNode->data = value;
		if (head == nullptr)
		{
			head = newNode;
			tail = head;
		}
		else
		{
			tail->next = newNode;
			tail = newNode;
		}
		count++;
	}

//-----------------------------------------------------------
// Inserts a value next to specific node.
//	node (ListNode<T>*): What node will have a new node next to it?
//	value (T): What value is inserted next to specific node?
//-----------------------------------------------------------
	void Insert(ListNode<T>* node, T value)
	{
		ListNode<T>* newNode = new ListNode<T>();
		newNode->next = node->next;
		newNode->data = value;
		node->next = newNode;
		count++;
	}

//-----------------------------------------------------------
// Returns a pointer of the head node of this linked list.
//	return (ListNode<T>*): returns pointer of head node of this linked list.
//-----------------------------------------------------------
	ListNode<T>* Begin()
	{
		if (head != nullptr)
		{
			return head;
		}
		return nullptr;
	}

//-----------------------------------------------------------
// Returns a pointer of the tail node of this linked list.
//	return (ListNode<T>*): returns pointer of tail node of this linked list.
//-----------------------------------------------------------
	ListNode<T>* End()
	{
		if (head != nullptr)
		{
			return tail;
		}
		return nullptr;
	}

//-----------------------------------------------------------
// Returns a copy of the head node of this linked list.
//	return (ListNode<T>): returns copy of head node of this linked list.
//-----------------------------------------------------------
	ListNode<T> First()
	{
		if (head != nullptr)
		{
			return *head;
		}		
		return ListNode<T> null;
	}

//-----------------------------------------------------------
// Returns a copy of the tail node of this linked list.
//	return (ListNode<T>): returns copy of tail node of this linked list.
//-----------------------------------------------------------
	ListNode<T> Last()
	{
		if (head != nullptr)
		{
			return *tail;
		}
		ListNode<T> null;
		return null;
	}

//-----------------------------------------------------------
// Returns a number of values in linked list.
//	return (int): returns number of value in linked list.
//-----------------------------------------------------------
	int Count()
	{
		return count;
	}

//-----------------------------------------------------------
// Removes node next to specific node from linked list.
//	node (ListNode<T>*): What node, next to this node, do you want removed?
//-----------------------------------------------------------
	void Erase(ListNode<T>* node)
	{
		if (node->next != nullptr)
		{
			ListNode<T>* del = node->next;
			node->next = node->next->next;
			delete del;
		}
		count--;
	}
//-----------------------------------------------------------
// Removes all nodes with specific value.
//	 value (T): What values will be removed from linked list?
//-----------------------------------------------------------
	void Remove(T value)
	{
		while (head->data == value)
		{
			popFront();
		}
		ListNode<T>* currentNode = head;
		while (currentNode != nullptr)
		{
			if (currentNode->next->data == value)
			{
				Erase(currentNode);
			}
			currentNode = currentNode->next;
		}
	}
//-----------------------------------------------------------
// Removes value from back of linked list.
//-----------------------------------------------------------
	void PopBack()
	{
		ListNode<T>* currentNode = head;
		if (count != 1)
		{
			if (currentNode != nullptr)
			{
				if (currentNode->next == tail)
				{
					tail = head;
					head->next = nullptr;
				}
				else
				{
					while (currentNode->next != tail)
					{
						currentNode = currentNode->next;
					}
					delete tail;
					currentNode->next = nullptr;	
					tail = currentNode;
				}
				count--;
			}
		}
		else if(count != 0)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
		}
	}
//-----------------------------------------------------------
// Removes value from front of linked list.
//-----------------------------------------------------------
	void PopFront()
	{
		if (head != nullptr)
		{
			ListNode<T>* del = head;
			head = head->next;
			delete del;
			count--;
		}
	}
//-----------------------------------------------------------
// Tests if linked list is empty.
//	retrun (bool): returns true if count is 0 or returns false.
//-----------------------------------------------------------
	bool Empty()
	{
		if (count == 0)
		{
			return true;
		}
		return false;
	}
//-----------------------------------------------------------
// Removes all values of linked list.
//-----------------------------------------------------------
	void Clear()
	{
		ListNode<T>* currentNode = head;
		if (currentNode != nullptr)
		{
			while (currentNode->next != nullptr)
			{
				ListNode<T>* del = currentNode;
				currentNode = currentNode->next;
				delete del;
			}
			count = 0;
			head = nullptr;
			tail = nullptr;
		}
	}
//-----------------------------------------------------------
// Sorts linked list with bubble sort.
//-----------------------------------------------------------
	void BubbleSort()
	{
		ListNode<T>* currentNode = head;
		float loops = 0;
		if (currentNode != nullptr)
		{
			if (currentNode->next != nullptr)
			{
				while (count != loops)
				{
					while (currentNode->next != nullptr)
					{
						if (currentNode->data > currentNode->next->data)
						{
							Swap(currentNode->data, currentNode->next->data);
						}
						currentNode = currentNode->next;
					}
					currentNode = head;
					loops++;
				}
			}
		}
	}
//-----------------------------------------------------------
// Sorts linked list with insertion sort.
//-----------------------------------------------------------
	void InsertionSort()
	{
		ListNode<T>* currentNode = head;
		ListNode<T>* insertNode = head;
		while (insertNode != nullptr)
		{
			while (currentNode != nullptr)
			{
				if (insertNode->data > currentNode->data)
				{
					Swap(insertNode->data, currentNode->data);
				}
				currentNode = currentNode->next;
			}
			insertNode = insertNode->next;
			currentNode = insertNode;
		}
	}
//-----------------------------------------------------------
// Search linked list with linear search.
//	value (T): what value will be searched?
//	return (ListNode<T>*): returns pointer to node with value
//-----------------------------------------------------------
	ListNode<T>* LinearSearch(T value)
	{
		ListNode<T>* currentNode = head;
		while (currentNode != nullptr)
		{
			if (currentNode->data == value)
			{
				return currentNode;;
			}
			currentNode = currentNode->next;
		}
		return nullptr;
	}
//-----------------------------------------------------------
// Search linked list with binary search.
//	value (T): what value will be searched?
//	return (ListNode<T>*): returns pointer to node with value
//-----------------------------------------------------------
	ListNode<T>* BinarySearch(T value)
	{
		if (head != nullptr)
		{
			InsertionSort();
			float max = count;
			float min = 0;
			float iterate = 0;
			float middle = 0;
			while (max >= min)
			{
				middle = (min + max) / 2;
				ListNode<T> * currentNode = head;
				while (iterate != middle)
				{
					if (currentNode->next != nullptr)
					{
						currentNode = currentNode->next;
						iterate++;
					}
					else
					{
						break;
					}
				}
				iterate = 0;
				if (currentNode->data == value)
				{
					return currentNode;
				}
				else if (currentNode->data > value)
				{
					max = middle - 1;
				}
				else if (currentNode->data < value)
				{
					min = middle + 1;
				}
			}
		}
		return nullptr;
	}

private:
	int count = 0;
	ListNode<T>* head = nullptr;
	ListNode<T>* tail = nullptr;
//-----------------------------------------------------------
// Swaps two values in linked list
//	value1 (T&): what value will be swapped?
//	value2 (T&): what value will be swapped?
//-----------------------------------------------------------
	void Swap(T& value1, T& value2)
	{
		T temp = value1;
		value1 = value2;
		value2 = temp;
	};
};

