#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//TODO - Representation

	SortedBag::BSTNode* currentNode;
	SortedBag::BSTNode* nextNode;

	void inorder_recursive(SortedBag::BSTNode* node, SortedBag::BSTNode*& nextNode, bool& found);
	SortedBag::BSTNode* inorderNext(SortedBag::BSTNode* node);

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

