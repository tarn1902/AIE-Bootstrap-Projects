/*----------------------------------------
File Name: TreeNode.h
Purpose: Holds data of each tree node
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once

#include "BinaryTreeApp.h"
template <typename T>
//-----------------------------------------------------------
// Object for holding data
//-----------------------------------------------------------
struct TreeNode
{
	T value;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;
};

