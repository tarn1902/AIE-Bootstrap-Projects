/*----------------------------------------
File Name: HashFunction.cpp
Purpose: Holds each method in namespace for HashFunction.h
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include "HashFunction.h"
//-----------------------------------------------------------
// Namespace with hash functions
//-----------------------------------------------------------
namespace HashFunction {
	typedef std::function< unsigned int(const char*, unsigned int)> HashFunc;
//-----------------------------------------------------------
// Previous example of a hash function (not used).
//	data (const char*): What string will be hashed?
//	length (unsigned int): What length is the string?
//	return (unsigned int): returns sequnece of numbers.
//-----------------------------------------------------------
	unsigned int badHash(const char* data, unsigned int length)
	{
		unsigned int hash = 0;
		for (unsigned int i = 0; i < length; ++i)
			hash += data[i];
		return hash;
	}
//-----------------------------------------------------------
// Better function for hashing strings
//	data (const char*): What string will be hashed?
//	length (unsigned int): What length is the string?
//	return (unsigned int): returns sequnece of numbers.
//-----------------------------------------------------------
	unsigned int BKDRHash(const char* data, unsigned int size) {
		unsigned int hash = 0;
		for (unsigned int i = 0; i < size; ++i) {
			hash = (hash * 1313) + data[i];
		}
		return (hash & 0x7FFFFFFF);
	}
}
