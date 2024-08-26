#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

using namespace std;

SortedBag::BSTNode* SortedBag::initNode(TComp e) {
	BSTNode* node = new BSTNode;
	node->info = e;
	node->left = nullptr;
	node->right = nullptr;
	return node;
}
// BC = TC = AC = Theta(1)


SortedBag::BSTNode* SortedBag::insertNode(BSTNode* node, TComp e) {
	if (node == nullptr) {
		node = initNode(e);
	}
	else {
		if (relation(e, node->info)) {
			node->left = insertNode(node->left, e);
		}
		else {
			node->right = insertNode(node->right, e);
		}
	}
	return node;
}
// BC = Theta(1) - when the inserted element is on the first level of the tree
// WC = Theta(n) - when the inserted element is on the last level of the tree
// TC = O(n) , n = nrElems = number of nodes in the tree

/*
SortedBag::BSTNode* SortedBag::removeNode(BSTNode* node, TComp e) {
	//if (node == nullptr) {
	//	// if the element is not in the tree
	//	return nullptr;
	//}

	if (node->info == e) {
		// if the element is a leaf
		if (node->left == nullptr) {
			// if the element has a right child
			BSTNode* right = node->right;
			delete node;
			return right;
		}
		if (node->right == nullptr) {
			// if the element has a left child
			BSTNode* left = node->left;
			delete node;
			return left;
		}
		BSTNode* min = minimumNode(node->right);
		node->info = min->info;
		node->right = removeNode(node->right, min->info);
	}
	else if (relation(e, node->info)) {
		// if the element is in the left subtree
		node->left = removeNode(node->left, e);
	}
	else {
	// if the element is in the right subtree
		node->right = removeNode(node->right, e);
	}
	return node;
}
*/

SortedBag::BSTNode* SortedBag::maximumNode(BSTNode* node) {
	// returns the node with the maximum value in the tree starting from the given node
	if (node == nullptr) {
		return nullptr;
	}
	if (node->right == nullptr) {
		return node;
	}
	return maximumNode(node->right);
}
// BC = Theta(1) - when the maximum element is on the first level of the tree
// WC = Theta(n) - when the maximum element is on the last level of the tree
// TC = O(n) , n = nrElems = number of nodes in the tree


SortedBag::BSTNode* SortedBag::removeNode(BSTNode* node, TComp e) {
	if (node == nullptr) {
		// the element is not in the tree
		return nullptr;
	}

	if (node->info == e)
	{
		// found the element
		if (node->left == nullptr && node->right == nullptr) {
			// case 1: no descendants (leaf node)
			delete node;
			return nullptr;
		}
		else if (node->left == nullptr) {
			// case 2: one descendant (right child only)
			BSTNode* rightChild = node->right;
			delete node;
			return rightChild;
		}
		else if (node->right == nullptr) {
			// case 2: one descendant (left child only)
			BSTNode* leftChild = node->left;
			delete node;
			return leftChild;
		}
		else {
			// case 3: two descendants 
			BSTNode* maxNode = maximumNode(node->left); // find the maximum of the left subtree
			node->info = maxNode->info;
			node->left = removeNode(node->left, maxNode->info);
		}
	}
	else if (relation(e, node->info)) {
		// if the element is in the left subtree
		node->left = removeNode(node->left, e);
	}
	else {
		// if the element is in the right subtree
		node->right = removeNode(node->right, e);
	}
	return node;
}
// BC = Theta(1) - when the element to be removed has one or zero descendants
// WC = Theta(n) - when the element to be removed has two descendants and the maximum element is on the last level of the tree
// TC = O(n) , n = nrElems = number of nodes in the tree


bool SortedBag::searchNode(BSTNode* node, TComp e) const {
	if (node == nullptr) {
		return false;
	}
	if (node->info == e) {
		return true;
	}
	else if (relation(e, node->info)) {
		return searchNode(node->left, e);
	}
	else {
		return searchNode(node->right, e);
	}
}
// BC = Theta(1) - when the element is on the first level of the tree
// WC = Theta(n) - when the element is on the last level of the tree
// TC = O(n) , n = nrElems = number of nodes in the tree


int SortedBag::nrOccurrencesNode(BSTNode* node, TComp e) const {
	// returns the number of occurrences of the element in the tree starting from the given node
	if (node == nullptr) {
		return 0;
	}
	if (node->info == e) {
		return 1 + nrOccurrencesNode(node->left, e);
	}
	else if (relation(e, node->info)) {
		return nrOccurrencesNode(node->left, e);
	}
	else {
		return nrOccurrencesNode(node->right, e);
	}
}
// BC = WC = TC = Theta(n), n = nrElems = number of nodes in the tree


void SortedBag::destroy(BSTNode* node) {
	if (node == nullptr) {
		return;
	}
	destroy(node->left);
	destroy(node->right);
	delete node;
}
// BC = WC = TC = Theta(n) , n = nrElems = number of nodes in the tree


SortedBag::SortedBag(Relation r) {

	this->nrElems = 0;
	this->root = nullptr;
	this->relation = r;

}
// BC = WC = TC = Theta(1)


void SortedBag::add(TComp e) {

	this->root = this->insertNode(this->root, e);
	this->nrElems++;
}
// BC = Theta(1) - when the inserted element is on the first level of the tree
// WC = Theta(n) - when the inserted element is on the last level of the tree
// TC = O(n) , n = nrElems = number of nodes in the tree


bool SortedBag::remove(TComp e) {

	if (this->search(e) == false) {
		return false;
	}
	else {
		this->root = this->removeNode(this->root, e);
		this->nrElems--;
		return true;
	}
}
// BC = Theta(1) - when the element to be removed has one or zero descendants
// WC = Theta(n) - when the element to be removed has two descendants and the maximum element is on the last level of the tree
// TC = O(n) , n = nrElems = number of nodes in the tree


bool SortedBag::search(TComp elem) const {

	return this->searchNode(this->root, elem);
}
// BC = Theta(1) - when the element is on the first level of the tree
// WC = Theta(n) - when the element is on the last level of the tree
// TC = O(n) , n = nrElems = number of nodes in the tree


int SortedBag::nrOccurrences(TComp elem) const {

	return this->nrOccurrencesNode(this->root, elem);
}
// BC = Theta(log(n)) - when the element is on the first level of the tree
// WC = Theta(n) - when the element is on the last level of the tree
// TC = O(n) , n = nrElems = number of nodes in the tree


int SortedBag::size() const {

	return this->nrElems;
}
// BC = WC = TC = Theta(1)


bool SortedBag::isEmpty() const {

	return this->size() == 0;
}
// BC = WC = TC = Theta(1)

void SortedBag::addOccurences(int nr, TComp elem) {

	if (nr < 0) {
		throw exception();
	}
	for (int i = 0; i < nr; i++) {
		this->add(elem);
	}
}
// BC = Theta(1) - when the number of occurrences is 0
// WC = Theta(n) - when the element is on the last level of the tree
// TC = O(n) , n = nrElems = number of nodes in the tree

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
// BC = WC = TC = Theta(1)


SortedBag::~SortedBag() {

	this->destroy(this->root);
}
// BC = WC = TC = Theta(n) , n = nrElems = number of nodes in the tree
