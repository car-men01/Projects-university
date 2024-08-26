#include "SetIterator.h"
#include "Set.h"
#include <exception>
using std::exception;

SetIterator::SetIterator(const Set& m) : set(m)
{
	this->current = this->set.head;
}
// BC = TC = WC = Theta(1)


void SetIterator::first() {
	this->current = this->set.head;
}
// BC = TC = WC = Theta(1)


void SetIterator::next() {
	if (this->current == nullptr || this->current->info == NULL_TELEM)
		throw exception();
	this->current = this->current->next;
}
// BC = TC = WC = Theta(1)


TElem SetIterator::getCurrent()
{
	if (this->current == nullptr || this->current->info == NULL_TELEM)
		throw exception();
	return this->current->info;
}
// BC = TC = WC = Theta(1)


bool SetIterator::valid() const {
	if (this->current == nullptr || this->current->info == NULL_TELEM)
		return false;
	else
		return true;
}
// BC = TC = WC = Theta(1)


void SetIterator::previous()
{
	if (this->current == nullptr || this->current->info == NULL_TELEM)
		throw exception();

	Set::SLLNode* elem = this->set.head;
	Set::SLLNode* last_elem = nullptr;

	while (elem != nullptr && elem->info != this->current->info)
	{
		if (elem->next != nullptr && elem->next->info == this->current->info)
			last_elem = elem;
		elem = elem->next;
	}

	if (this->current == this->set.head)
		this->current = nullptr;
	else
		this->current = last_elem;
}
// BC = Theta(1), TC = O(n), WC = Theta(n)
