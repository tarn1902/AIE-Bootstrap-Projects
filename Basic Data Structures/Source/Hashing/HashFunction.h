/*----------------------------------------
File Name: HashFunction.h
Purpose: Holds namespace with hash functions
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#include <functional>

//-----------------------------------------------------------
// Namespace with hash functions
//-----------------------------------------------------------
namespace HashFunction
{
	typedef std::function< unsigned int(const char*, unsigned int)> HashFunc;
	// implementation of a basic addition hash    
	unsigned int badHash(const char* data, unsigned int length);
	// ADD YOUR FUNCTIONS HERE
	unsigned int BKDRHash(const char* data, unsigned int size);
	// a helper to access a default hash function
	static HashFunc default = BKDRHash;
}

