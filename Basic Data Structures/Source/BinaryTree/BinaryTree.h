/*----------------------------------------
File Name: BinaryTree.h
Purpose: Controls how a binary tree behaves
Author: Tarn Cooper
Modified: 07 May 2019
------------------------------------------
Copyright 2019 Tarn Cooper.
-----------------------------------*/
#pragma once
#include "TreeNode.h"
template<typename T>
//-----------------------------------------------------------
// Object for controling a binary tree
//-----------------------------------------------------------
class BinaryTree
{
public:
//-----------------------------------------------------------
// Inserts value into tree.
//	value (T): What value is inserted?
//-----------------------------------------------------------
	void Insert(T value)
	{
		if (pRoot == nullptr)
		{
			pRoot = new TreeNode<T>();
			pRoot->value = value;
		}
		else
		{
			TreeNode<T>* currentNode = pRoot;
			TreeNode<T>* parentNode = pRoot;
			while (currentNode != nullptr)
			{
				if (currentNode->value > value)
				{
					parentNode = currentNode;
					currentNode = currentNode->left;
				}
				else if (currentNode->value < value)
				{
					parentNode = currentNode;
					currentNode = currentNode->right;
				}
				else if (currentNode->value == value)
				{
					break;
				}
			}
			if (parentNode->value < value)
			{
				parentNode->right = new TreeNode<T>();
				parentNode->right->value = value;
			}
			else if (parentNode->value > value)
			{
				parentNode->left = new TreeNode<T>();
				parentNode->left->value = value;
			}

		}
	}

//-----------------------------------------------------------
// Finds value in tree.
//	value (T): What value is to be found?
//	ppOutNode (TreeNode<T>**): Where to put pointer to current node?
//	ppOutParent (TreeNode<T>**): Where to put pointer to parent of current node?
//	return (TreeNode<T>*): Returns the node that matches or nullptr if not found.
//-----------------------------------------------------------
	TreeNode<T>* Find(T value, TreeNode<T>** ppOutNode, TreeNode<T>** ppOutParent)
	{
		TreeNode<T>* currentNode = pRoot;
		TreeNode<T>* parentNode = nullptr;
		while (currentNode != nullptr)
		{
			if (currentNode->value == value)
			{
				*ppOutNode = currentNode;
				*ppOutParent = parentNode;
				return currentNode;
			}
			else
			{
				if (currentNode->value > value)
				{
					parentNode = currentNode;
					currentNode = currentNode->left;
				}
				else if (currentNode->value < value)
				{
					parentNode = currentNode;
					currentNode = currentNode->right;
				}
			}
		}
		return nullptr;
	}
//-----------------------------------------------------------
// Finds value in tree
//	value (T): What value is to be found?
//	return (TreeNode<T>*): Returns the node that matches or nullptr if not found.
//-----------------------------------------------------------
	TreeNode<T>* Find(T value)
	{
		TreeNode<T>* currentNode = pRoot;
		TreeNode<T>* parentNode = nullptr;
		while (currentNode != nullptr)
		{
			if (currentNode->value == value)
			{
				return currentNode;
			}
			else
			{
				if (currentNode->value > value)
				{
					parentNode = currentNode;
					currentNode = currentNode->left;
				}
				else if (currentNode->value < value)
				{
					parentNode = currentNode;
					currentNode = currentNode->right;
				}
			}
		}
		return nullptr;
	}

//-----------------------------------------------------------
// Removes value from tree
//	 value (T): What value is to be removed?
//-----------------------------------------------------------
	void Remove(T value)
	{
		TreeNode<T>* currentNode;
		TreeNode<T>* parentNode;
		if (Find(value, &currentNode, &parentNode))
		{
			if (pRoot != nullptr)
			{
				if (currentNode->right != nullptr)
				{
					TreeNode<T>* minParentNode = currentNode;
					TreeNode<T>* minNode = currentNode->right;
					while (minNode->left != nullptr)
					{
						minParentNode = minNode;
						minNode = minNode->left;
					}
					currentNode->value = minNode->value;
					if (minParentNode->left == minNode)
					{
						delete minParentNode->left;
						minParentNode->left = nullptr;
					}
					else if (minParentNode->right == minNode)
					{
						delete minParentNode->right;
						minParentNode->right = nullptr;
					}
				}
				else if (currentNode->right == nullptr)
				{
					if (pRoot == currentNode)
					{
						pRoot = currentNode->left;
					}
					else if (parentNode->left == currentNode)
					{
						delete parentNode->left;
						parentNode->left = nullptr;
					}
					else if (parentNode->right == currentNode)
					{
						delete parentNode->right;
						parentNode->right = nullptr;

					}

				}
			}
		}
	}

//-----------------------------------------------------------
// clears all values from tree.
//-----------------------------------------------------------
	void Clear()
	{
		if (pRoot != nullptr)
		{
			while (pRoot->left != nullptr || pRoot->right != nullptr)
			{
				TreeNode<T>* currentNode = pRoot;
				if (pRoot->left != nullptr)
				{
					while (currentNode->left != nullptr || currentNode->right != nullptr)
					{
						currentNode = pRoot;
						if (currentNode->left != nullptr)
						{
							TreeNode<T>* minNode = currentNode;
							while (minNode->left != nullptr)
							{
								minNode = minNode->left;
							}
							Remove(minNode->value);
						}
						if (currentNode->right != nullptr)
						{
							TreeNode<T>* maxNode = currentNode;
							while (maxNode->right != nullptr)
							{
								maxNode = maxNode->right;
							}
							Remove(maxNode->value);
						}
					}
				}
				if (pRoot->right != nullptr)
				{
					while (currentNode->left != nullptr || currentNode->right != nullptr)
					{
						if (currentNode->left != nullptr)
						{
							TreeNode<T>* minNode = currentNode;
							while (minNode->left != nullptr)
							{
								minNode = minNode->left;
							}
							Remove(minNode->value);
						}
						if (currentNode->right != nullptr)
						{
							TreeNode<T>* maxNode = currentNode;
							while (maxNode->right != nullptr)
							{
								maxNode = maxNode->right;
							}
							Remove(maxNode->value);
						}
					}
				}
			}
		}
		delete pRoot;
	}
//-----------------------------------------------------------
// clears all values from tree.
//	renderer (aie::Render2d*): What will be used to render image?
//	selected (TreeNode<T>*): What tree node will be selected from tree?
//	m_font (aie::Font*): What font will be used for texts?
//-----------------------------------------------------------
	void draw(aie::Renderer2D* renderer, TreeNode<T>* selected, aie::Font* m_font)
	{
		draw(renderer, pRoot, 640, 680, 640, selected, m_font);
	}
	void draw(aie::Renderer2D* renderer, TreeNode<T>* pNode, float x, float y, float horizontalSpacing, TreeNode<T>* selected, aie::Font* m_font)
	{
		horizontalSpacing /= 2;
		if (pNode != nullptr) 
		{
			if (pNode->left != nullptr)
			{
				renderer->setRenderColour(1, 0, 0);
				renderer->drawLine(x, y, x - horizontalSpacing, y - 80);
				draw(renderer, pNode->left, x - horizontalSpacing,
					y - 80, horizontalSpacing, selected, m_font);
			}
			if (pNode->right) {
				renderer->setRenderColour(1, 0, 0);
				renderer->drawLine(x, y, x + horizontalSpacing, y - 80);
				draw(renderer, pNode->right, x + horizontalSpacing,
					y - 80, horizontalSpacing, selected, m_font);
			}
			static char buffer[10];
			sprintf_s(buffer, "%d", pNode->value);

			renderer->setRenderColour(1, 1, 0);
			renderer->drawCircle(x, y, 30);

			if (pNode == selected)
				renderer->setRenderColour(.5, .5, 0);
			else
				renderer->setRenderColour(0, 0, 0);
			renderer->drawCircle(x, y, 28);

			renderer->setRenderColour(1, 1, 1);
			renderer->drawText(m_font, buffer, x - 12, y - 10);
		}
	}
	TreeNode<T>* pRoot = nullptr;	

//-----------------------------------------------------------
// Contructs this object
//-----------------------------------------------------------
	BinaryTree() 
	{

	}

//-----------------------------------------------------------
// Destroys this object
//-----------------------------------------------------------
	~BinaryTree()
	{
			Clear();
	}
};


