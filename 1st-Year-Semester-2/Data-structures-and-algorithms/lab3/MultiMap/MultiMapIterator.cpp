#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <iostream>

using namespace std;

MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {

	this->currKey = this->col.head;

	if (this->col.head == -1) {
		this->currValue = -1;
	}
	else {
		this->currValue = this->col.nodes[this->col.head].info->headS;
	}
}
// BC = WC = TC = Theta(1)

TElem MultiMapIterator::getCurrent() const{

	if (this->currKey == -1) {
		throw std::exception();
	}
	TValue v = this->col.nodes[this->currKey].info->nodesS[this->currValue].infoS;
	TKey k = this->col.nodes[this->currKey].keyInfo;
	return make_pair(k, v);

}
// BC = WC = TC = Theta(1)

bool MultiMapIterator::valid() const {

	if (this->currValue == -1 && this->currKey == -1) {
		return false;
	}
	return true;
}
// BC = WC = TC = Theta(1)

void MultiMapIterator::next() {

	if (!this->valid()) {
		throw std::exception();
	}
	if (this->col.nodes[this->currKey].info->nodesS[this->currValue].nextS != -1) {		
		this->currValue = this->col.nodes[this->currKey].info->nodesS[this->currValue].nextS;
	}
	else {
		this->currKey = this->col.nodes[this->currKey].next;
		if (this->currKey != -1) {
			this->currValue = this->col.nodes[this->currKey].info->headS;
		}
		else {
			this->currValue = -1;
		}
	}
}
// BC = WC = TC = Theta(1)

void MultiMapIterator::first() {

	this->currKey = this->col.head;
	this->currValue = this->col.nodes[this->col.head].info->headS;
}
// BC = WC = TC = Theta(1)

void MultiMapIterator::jumpForward(int k) {

	if (k <= 0 || !this->valid()) {
		throw std::exception();
	}
	int i = 0;
	while (i < k && this->valid()) {
		this->next();
		i++;
	}
}
// BC = Theta(1), WC = Theta(k)
// TC = O(k), k - number of elements to jump over
