#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <iostream>

using namespace std;


//void SortedBagIterator::inorder_recursive(SortedBag::BSTNode* node, SortedBag::BSTNode*& nextNode, bool& found) {
//	// find the next node in the inorder traversal of the tree
//	if (node == nullptr) {
//		return;
//	}
//	inorder_recursive(node->left, this->nextNode, found);
//	// visit the node
//	if (found) {
//		if (this->nextNode == nullptr) {
//			this->nextNode = node;
//		}
//		return;
//	}
//	if (node == this->currentNode) {
//		found = true;
//	}
//	inorder_recursive(node->right, this->nextNode, found);
//}
//// BC = WC = TC = Theta(n)
//
//SortedBag::BSTNode* SortedBagIterator::inorderNext(SortedBag::BSTNode* node) {
//	this->currentNode = node;
//	SortedBag::BSTNode* nextNode = nullptr;
//	bool found = false;
//	inorder_recursive(bag.root, nextNode, found);
//	return nextNode;
//}


void SortedBagIterator::inorder_recursive(SortedBag::BSTNode* node, SortedBag::BSTNode*& successor, bool& found) {
	// find the next node in the inorder traversal of the tree
	if (node == nullptr) {
		return;
	}
	inorder_recursive(node->left, successor, found);

	// visit the node
	if (found && successor == nullptr) {
		successor = node;
		return;
	}
	if (node == this->currentNode) {
		found = true;
	}
	inorder_recursive(node->right, successor, found);
}
// BC = WC = TC = Theta(n)

SortedBag::BSTNode* SortedBagIterator::inorderNext(SortedBag::BSTNode* node) {
	SortedBag::BSTNode* successor = nullptr;
	bool found = false;
	this->currentNode = node;
	inorder_recursive(bag.root, successor, found);
	return successor;
}
// BC = WC = TC = Theta(n)

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->currentNode = bag.root;
	this->nextNode = nullptr;

	while (this->currentNode && this->currentNode->left != nullptr) {
		this->currentNode = this->currentNode->left;
		this->nextNode = this->currentNode;
	}
	if (this->currentNode) {
		this->nextNode = inorderNext(this->currentNode);
	}
}
// BC = WC = TC = Theta(n)

TComp SortedBagIterator::getCurrent() {

	if (!valid()) {
		throw exception();
	}
	return this->currentNode->info;
}
// BC = WC = TC = Theta(1)

bool SortedBagIterator::valid() {
	
	return this->currentNode != nullptr;
}
// BC = WC = TC = Theta(1)

void SortedBagIterator::next() {
	
	if (!valid()) {
		throw exception();
	}
	this->currentNode = this->nextNode;
	if (this->currentNode) {
		this->nextNode = inorderNext(this->currentNode);
	}
}
// BC = WC = TC = Theta(n)

void SortedBagIterator::first() {
	
	this->currentNode = bag.root;
	this->nextNode = nullptr;

	while (this->currentNode && this->currentNode->left != nullptr) {
		this->currentNode = this->currentNode->left;
		this->nextNode = this->currentNode;
	}

	if (this->currentNode) {
		this->nextNode = inorderNext(this->currentNode);
	}
}
// BC = WC = TC = Theta(n)
