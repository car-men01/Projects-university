#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
#include <iostream>

using namespace std;

SortedBag::BSTNode* SortedBagIterator::inorderNext(SortedBag::BSTNode* node) {
	if (node == nullptr) {
		return nullptr;
	}
	if (node->right != nullptr) {
		node = node->right;
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}
	SortedBag::BSTNode* parent = nullptr;
	currentNode = bag.root;
	while (currentNode && currentNode != node) {
		if (bag.relation(node->info, currentNode->info)) {
			parent = currentNode;
			currentNode = currentNode->left;
		}
		else {
			currentNode = currentNode->right;
		}
	}
	return parent;
}

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->currentNode = bag.root;
	this->nextNode = nullptr;

	while (currentNode && currentNode->left != nullptr) {
		currentNode = currentNode->left;
		this->nextNode = currentNode;
	}

	if (currentNode) {
		this->nextNode = inorderNext(currentNode);
	}

}

TComp SortedBagIterator::getCurrent() {

	if (!valid()) {
		throw exception();
	}
	return currentNode->info;
}

bool SortedBagIterator::valid() {
	
	return currentNode != nullptr;
}

void SortedBagIterator::next() {
	
	if (!valid()) {
		throw exception();
	}
	currentNode = nextNode;
	if (currentNode) {
		nextNode = inorderNext(currentNode);
	}
}

void SortedBagIterator::first() {
	
	this->currentNode = bag.root;
	while (this->currentNode && this->currentNode->left != nullptr) {
		this->currentNode = this->currentNode->left;
		this->nextNode = this->currentNode;
	}

	std::cout << this->bag.size() << std::endl;

	if (this->currentNode) {
		this->nextNode = inorderNext(this->currentNode);
	}
}

