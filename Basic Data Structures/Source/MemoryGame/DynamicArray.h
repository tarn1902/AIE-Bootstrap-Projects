/*----------------------------------------
File Name: DynamicArray.h
Purpose: Controls how a dynamic array behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
template<typename T>
//-----------------------------------------------------------
// Object for controling a dynamic array
//-----------------------------------------------------------
class DynamicArray
{
public:
	//-----------------------------------------------------------
	// Contructs this object
	//-----------------------------------------------------------
	DynamicArray() {}
	//-----------------------------------------------------------
	// Destroys this object
	//-----------------------------------------------------------
	~DynamicArray()
	{
		delete[]data;
	}
	//-----------------------------------------------------------
	// Copys other dynamic array with brackets
	//-----------------------------------------------------------
	DynamicArray(const DynamicArray& other)
	{
		Clear();
		for (int i = 0; i < other.usedElements; i++)
		{
			AddToEnd(other.data[i]);
		}
	}
	//-----------------------------------------------------------
	// Copys other dynamic array with = sign
	//-----------------------------------------------------------
	DynamicArray& operator= (const DynamicArray& other)
	{
		Clear();
		for (int i = 0; i < other.usedElements; i++)
		{
			AddToEnd(other.data[i]);
		}
		return *this;
	}
	//-----------------------------------------------------------
	// Creates array for this object
	//	size (int): How big should the array be?
	//-----------------------------------------------------------
	void CreateArray(int size)
	{
		data = new T[size];
		allocatedvalues = size;

	}
	//-----------------------------------------------------------
	// Inserts value to start of array.
	//	value (T): What value is inserted?
	//-----------------------------------------------------------
	void AddToStart(T value)
	{
		for (int i = usedElements; i > 0; i--)
		{
			data[i] = data[i - 1];
		}
		data[0] = value;
		usedElements++;
	}

	//-----------------------------------------------------------
	// Inserts value to middle of array.
	//	value (T): What value is inserted?
	//-----------------------------------------------------------
	void AddToMid(T value)
	{
		for (int i = usedElements; i > usedElements / 2; i--)
		{
			data[i] = data[i - 1];
		}
		data[usedElements / 2] = value;
		usedElements++;
	}

	//-----------------------------------------------------------
	// Inserts value to middle of array.
	//	value1 (T): What value is inserted?
	//	value2 (T): What value is inserted?
	//-----------------------------------------------------------
	void AddToMid(T value1, T value2)
	{
		AddToMid(value1);
		AddToMid(value2);
	}

	//-----------------------------------------------------------
	// Inserts value to end of array.
	//	value (T): What value is inserted?
	//-----------------------------------------------------------
	void AddToEnd(T value)
	{
		if (allocatedvalues == usedElements)
		{
			T* newData = new T[allocatedvalues * 2];
			for (int i = 0; i < allocatedvalues; i++)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
			allocatedvalues *= 2;
		}
		data[usedElements] = value;
		usedElements += 1;
	}
	//-----------------------------------------------------------
	// Removes value from start of array.
	//-----------------------------------------------------------
	void RemoveFromStart()
	{
		for (int i = 0; i < usedElements; i++)
		{
			data[i] = data[i + 1];
		}
		usedElements--;
		if (usedElements < 0)
		{
			usedElements = 0;
		}
	}
	//-----------------------------------------------------------
	// Removes value from middle of array.
	//-----------------------------------------------------------
	void RemoveFromMid()
	{
		for (int i = usedElements / 2; i < usedElements; i++)
		{
			data[i] = data[i + 1];
		}
		usedElements--;
		if (usedElements < 0)
		{
			usedElements = 0;
		}
	}
	//-----------------------------------------------------------
	// Removes value from end of array.
	//-----------------------------------------------------------
	void RemoveFromEnd()
	{
		usedElements--;
		if (usedElements < 0)
		{
			usedElements = 0;
		}
	}
	//-----------------------------------------------------------
	// Reduces the space left empty
	//-----------------------------------------------------------
	void ReduceSpace()
	{
		if (usedElements == 0)
		{
			allocatedvalues = 1;
		}
		else
		{
			allocatedvalues = usedElements;
		}
		T* newData = new T[allocatedvalues * 2];
		for (int i = 0; i < allocatedvalues; i++)
		{
			newData[i] = data[i];
		}
		delete data;
		data = newData;
	}

	//-----------------------------------------------------------
	// Resets array to zero
	//-----------------------------------------------------------
	void Clear()
	{
		usedElements = 0;
	}

	//-----------------------------------------------------------
	// Sorts array using bubble sort
	//-----------------------------------------------------------
	void BubbleSort()
	{
		for (int i = 0; i < usedElements - 1; i++)
		{
			for (int j = usedElements - 1; j > i; j--)
			{
				if (data[j] < data[j - 1])
				{
					Swap(data[j], data[j - 1]);
				}
			}
		}
	}

	//-----------------------------------------------------------
	// Sorts array using insertion sort
	//-----------------------------------------------------------
	void InsertionSort()
	{
		for (int i = 1; i < usedElements; i++)
		{
			T key = data[i];
			int j = i - 1;
			while (j >= 0 && data[j] > key)
			{
				data[j + 1] = data[j];
				j = j - 1;
				data[j + 1] = key;
			}
		}
	}

	//-----------------------------------------------------------
	// Searches array using linear search
	//	value (int): What value should be searched?
	//	return (int): returns index of position in array
	//-----------------------------------------------------------
	int LinearSearch(T value)
	{
		for (int i = 0; i < usedElements; i++)
		{
			if (data[i] == value)
			{
				return i;
			}
		}
		return -1;
	}

	//-----------------------------------------------------------
	// Searches array using binary search
	//	value (int): What value should be searched?
	//	return (int): returns index of position in array
	//-----------------------------------------------------------
	int BinarySearch(T value)
	{
		InsertionSort();
		int max = usedElements;
		int min = 0;
		while (max >= min)
		{
			int middle = (min + max) / 2;
			if (data[middle] == value)
			{
				return middle;
			}
			else if (data[middle] > value)
			{
				max = middle - 1;
			}
			else if (data[middle] < value)
			{
				min = middle + 1;
			}
		}
		return -1;
	}

	T* data = nullptr;
	int allocatedvalues = 0;
	int usedElements = 0;

private:
	//-----------------------------------------------------------
	// Swaps two values in linked list
	//	value1 (T&): what value will be swapped?
	//	value2 (T&): what value will be swapped?
	//-----------------------------------------------------------
	void Swap(T & value1, T & value2)
	{
		T temp = value1;
		value1 = value2;
		value2 = temp;
	};

};
