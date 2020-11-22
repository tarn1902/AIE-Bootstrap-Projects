/*----------------------------------------
File Name: HashTable.h
Purpose: Controls how a hash table behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "HashFunction.h"
template<typename KeyType, typename T>
//-----------------------------------------------------------
// Object for controling a hash table
//-----------------------------------------------------------
class HashTable {
public:
//-----------------------------------------------------------
// Contructs this object based on size
//	size (unsigned int): how big should hashtable be?
//-----------------------------------------------------------
	HashTable(unsigned int size)
		: m_size(size), m_data(new T[size]) {}
//-----------------------------------------------------------
// Destroys this object
//-----------------------------------------------------------
	~HashTable() { delete[] m_data; }
//-----------------------------------------------------------
// Sets and returns values within hashtable.
//	key (const KeyType&): What key to use?
//	return (T&): returns value from key.
//-----------------------------------------------------------
	T& operator [] (const KeyType& key) {
		auto hashedKey = hashFunction(key) % m_size;
		return m_data[hashedKey];
	}
//-----------------------------------------------------------
// Sets and returns values within hashtable. Same as above.
//	key (const KeyType&): What key to use?
//	return (const T&): returns value from key.
//-----------------------------------------------------------
	const T& operator [] (const KeyType& key) const {
		auto hashedKey = hashFunction(key) % m_size;
		return m_data[hashedKey];
	}
private:
//-----------------------------------------------------------
// Changes key into a hash sequence
//	key(const KeyType&): What key to hash?
//	return (unsigned int): return hash sequence
//-----------------------------------------------------------
	unsigned int hashFunction(const KeyType& key)
	{
		return HashFunction::default(key, 10);
	}
	T* m_data;
	unsigned int m_size;
};

