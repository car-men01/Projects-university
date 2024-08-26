#include "Set.h"
#include "SetITerator.h"
#include <iostream>

using std::cout;
using std::endl;

Set::Set() {

	head = new SLLNode;

	head->info = NULL_TELEM;
	head->next = nullptr;
	this->size_list = 0;
}
// BC = TC = WC = Theta(1)


bool Set::add(TElem elem) {

	SLLNode* current = head;
	SLLNode* last_elem = nullptr;

	while (current != nullptr && current->info != elem)
	{
		if (current->next == nullptr)
			last_elem = current;
		current = current->next;
		
	}

	// if the elem is already in the set we don't add it
	if (current != nullptr)
		return false;

	// if the set is empty we add the elem
	if (head->info == NULL_TELEM) {
		head->info = elem;
		head->next = nullptr;
	}

	//if the set is not empty we add the elem at the end
	else {
		SLLNode* newNode = new SLLNode;
		newNode->info = elem;
		newNode->next = nullptr;

		last_elem->next = newNode;
	}
	this->size_list++;
	return true;
}
// BC = Theta(1), TC = O(n), WC = Theta(n)


bool Set::remove(TElem elem) {

	SLLNode* current = head;
	SLLNode* last_elem = nullptr;

	if (this->size() == 1 && this->head->info == elem) {
		head->info = NULL_TELEM;
		this->size_list--;
		return true;
	}

	while (current != nullptr && current->info != elem) {
		if (current->next != nullptr && current->next->info == elem)
			last_elem = current;
		current = current->next;
	}

	// if the elem is not in the set we can't remove it
	if (current == nullptr)
		return false;

	// if the elem is the head of the list
	if (current == head) {
		head = head->next;
		delete current;
	}

	else {
		// if the elem is not the head of the list
		last_elem->next = current->next;
		delete current;
	}

	this->size_list--;
	return true;
}
// BC = Theta(1), TC = O(n), WC = Theta(n)


bool Set::search(TElem elem) const {

	SLLNode* current = head;
	while (current != nullptr && current->info != elem) {
		current = current->next;
	}

	if (current != nullptr)
		return true;

	return false;
}
// BC = Theta(1), TC = O(n), WC = Theta(n)


int Set::size() const {

	return this->size_list;
}
// BC = TC = WC = Theta(1)

bool Set::isEmpty() const {

	if (head->info == NULL_TELEM)
		return true;

	return false;
}
// BC = TC = WC = Theta(1)


Set::~Set() {

	SLLNode* current = head;

	while (current != nullptr) {
		SLLNode* next = current->next;
		delete current;
		current = next;
	}
}
// BC = Theta(1), TC = O(n), WC = Theta(n)


SetIterator Set::iterator() const {
	return SetIterator(*this);
}
// BC = TC = WC = Theta(1)
