#pragma once
#include "BSTNode.h"
#include <vector>
template <class T>
class BinaryTree
{
	void addItemToArray(BSTNode<T>* node, int &pos, int *arr);
public:
	BSTNode<T> *root;
	BinaryTree();
	void add(T item);
	bool remove(T item);
	void clear();
	int count();

	T* toArray();
	void printInOrder();
	void printInOrder(BSTNode<T> *node);
	void printPreOrder();
	void printPreOrder(BSTNode<T> *node);
	void printPostOrder();
	void printPostOrder(BSTNode<T> *node);
	
	~BinaryTree();
};

template <class T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template <class T>
void BinaryTree<T>::add(T item)
{
	
}
template <class T>
int BinaryTree<T>::count()
{
	return 0;
}
template <class T>
bool BinaryTree<T>::remove(T item)
{

}


/**
	Helper Function to put the binary tree into a sorted array;

*/
template <class T>
void BinaryTree<T>::addItemToArray(BSTNode<T>* node, int &pos, int *arr)
{
	if (node != nullptr)
	{
		addItemToArray(node->getLeft(), pos, arr);
		arr[pos] = node->getItem();
		pos++;
		addItemToArray(node->getRight(), pos, arr);
	}

}

/**
	This function is used to convert this binary tree into a sorted array.

*/
template <class T>
T* BinaryTree<T>::toArray()
{
	T *arr = new T[root->count()];
	int pos = 0;
	addItemToArray(root, pos, arr);
	return arr;
}

template <class T>
void BinaryTree<T>::clear()
{
	delete root;
	root = nullptr;
}
template <class T>
BinaryTree<T>::~BinaryTree()
{
	delete root;
}



/*
Print the entire tree using in order traversal
*/
template<class T>
void BinaryTree<T>::printInOrder()
{
	this->printInOrder(root);
	cout << endl;
}
/*
Print a subtree using in order traversal
*/
template<class T>
void BinaryTree<T>::printInOrder(BSTNode<T> *node)
{
	
	
}
/*
Print the entire tree using pre order traversal
*/
template<class T>
void BinaryTree<T>::printPreOrder()
{
	this->printPreOrder(root);
	cout << endl;
}

/*
Print a subtree using post order traversal
*/
template<class T>
void BinaryTree<T>::printPreOrder(BSTNode<T> *node)
{

	
}

/*
	Print the entire tree using post order traversal	
*/
template<class T>
void BinaryTree<T>::printPostOrder()
{
	this->printPostOrder(root);
	cout << endl;
}
/*
		Print a subtree using post order traversal
*/
template<class T>
void BinaryTree<T>::printPostOrder(BSTNode<T> *node)
{

	
}