#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;


SortedMultiMap::SortedMultiMap(Relation r) {
	this->relation = r;
	this->m = 13;
	this->nrElems = 0;
	this->firstEmpty = 0;

	// initialize the hash table
	this->hashTable = new TableKeyValue[this->m];

	this->next = new int[this->m];
	for (int i = 0; i < this->m; i++) {
		this->next[i] = -1;
	}

	this->keyInfo = new TKey[this->m];
	for (int i = 0; i < this->m; i++) {
		this->keyInfo[i] = NULL_TKEY;
	}

	// initialize the dynamic array for each unique key in the hash table
	for (int i = 0; i < this->m; i++) {
		this->hashTable[i].sizeV = 0;
		this->hashTable[i].capacityV = 10;

		this->hashTable[i].values = new TValue[this->hashTable[i].capacityV];
		for (int j = 0; j < this->hashTable[i].capacityV; j++) {
			this->hashTable[i].values[j] = NULL_TVALUE;
		}
	}
}
// BC = TC = WC = Theta(m * cap)
// m = capacity of the hash table
// cap = capacity of the dynamic array for each unique key in the hash table

int SortedMultiMap::hashF(TKey k) const {
	// hash function - division method
	return k % this->m;
}
// BC = TC = WC = Theta(1)

void SortedMultiMap::changeFirstEmpty() {
	// change the first empty position in the hash table to the next empty position
	this->firstEmpty++;
	if (this->firstEmpty < this->m && this->keyInfo[this->firstEmpty] != NULL_TKEY) {
		while (this->firstEmpty < this->m && this->keyInfo[this->firstEmpty] != NULL_TKEY) {
			this->firstEmpty++;
		}
	}
}
// BC = Theta(1) - the first empty position is the next position in the hash table
// TC = O(m) - the first empty position is anywhere in the hash table
// WC = Theta(m) - the first empty position is the last position in the hash table

void SortedMultiMap::resizeValues(int pos) {
	// resize the dynamic vector of values from hashTable at position pos
	int newCapacity = this->hashTable[pos].capacityV * 2;
	TValue* newValues = new TValue[newCapacity];

	for (int i = 0; i < this->hashTable[pos].capacityV; i++) {
		newValues[i] = this->hashTable[pos].values[i];
	}
	for (int i = this->hashTable[pos].capacityV; i < newCapacity; i++) {
		newValues[i] = NULL_TVALUE;
	}

	delete[] this->hashTable[pos].values;
	this->hashTable[pos].values = newValues;
	this->hashTable[pos].capacityV = newCapacity;
}
// BC = TC = WC = Theta(cap) - cap = capacity of the dynamic array for each unique key in the hash table

void SortedMultiMap::resizeHashTable() {
	int oldM = this->m;
	this->m = this->m * 2;
	this->firstEmpty = 0;
	this->nrElems = 0;

	TableKeyValue* oldHashTable = this->hashTable;
	int* oldNext = this->next;
	TKey* oldKeyInfo = this->keyInfo;

	this->hashTable = new TableKeyValue[this->m];
	this->next = new int[this->m];
	this->keyInfo = new TKey[this->m];

	for (int i = 0; i < this->m; i++) {
		this->next[i] = -1;
		this->keyInfo[i] = NULL_TKEY;
		this->hashTable[i].sizeV = 0;
		this->hashTable[i].capacityV = 10;
		this->hashTable[i].values = new TValue[this->hashTable[i].capacityV];
		for (int j = 0; j < this->hashTable[i].capacityV; j++) {
			this->hashTable[i].values[j] = NULL_TVALUE;
		}
	}

	for (int i = 0; i < oldM; i++) {
		for (int j = 0; j < oldHashTable[i].sizeV; j++) {
			//this->add(oldKeyInfo[i], oldHashTable[i].values[j]);

			int c = oldKeyInfo[i];
			int v = oldHashTable[i].values[j];

			// add the (c, v) pair
			this->nrElems++;
			int pos = this->hashF(c);  // the position in the hash table where the element should be added

			if (this->keyInfo[pos] == c) {
				// the key is already in the hash table so we have to add the new value in the dynamic vector

				this->hashTable[pos].values[this->hashTable[pos].sizeV] = v;
				this->hashTable[pos].sizeV++;

				// resize the dynamic vector if it is full
				if (this->hashTable[pos].sizeV == this->hashTable[pos].capacityV) {
					this->resizeValues(pos);
				}
			}
			else if (this->keyInfo[pos] == NULL_TKEY) {
				// the position is empty

				this->keyInfo[pos] = c; // add the key in the hash table
				this->next[pos] = -1;

				if (pos == this->firstEmpty) {
					this->changeFirstEmpty();
				}

				// add the value v in the dynamic vector from hashTable
				this->hashTable[pos].values[this->hashTable[pos].sizeV] = v;
				this->hashTable[pos].sizeV++;

				// resize the dynamic vector if it is full
				if (this->hashTable[pos].sizeV == this->hashTable[pos].capacityV) {
					this->resizeValues(pos);
				}
			}
			else {
				// the position is not empty so we have to find the next empty position starting from pos

				int current = pos;
				while (this->next[current] != -1) {
					current = this->next[current];
				}

				if (this->next[current] == -1) {
					// add the element at the end of the list
					this->keyInfo[this->firstEmpty] = c;
					this->next[this->firstEmpty] = -1;
					this->next[current] = this->firstEmpty;
					this->changeFirstEmpty();
				}

				// add the value v in the dynamic vector from hashTable
				this->hashTable[pos].values[this->hashTable[pos].sizeV] = v;
				this->hashTable[pos].sizeV++;

				// resize the dynamic vector if it is full
				if (this->hashTable[pos].sizeV == this->hashTable[pos].capacityV) {
					this->resizeValues(pos);
				}

			}
		}
	}

	delete[] oldHashTable;
	delete[] oldNext;
	delete[] oldKeyInfo;
}
// BC = Theta(m * cap + m^2 * size) - resizing a hash table where all the keys are on a different position + changing the first empty
// TC = O(m * cap + m * size * (m + cap)) - resizing a hash table where all the keys are on the same position
// WC = Theta(m * cap + m * size * (m + cap)) - resizing a hash table where all the keys are in the same position
// m = capacity of the hash table
// size = the size of the dynamic array for each unique key in the hash table
// cap = capacity of the dynamic array for each unique key in the hash table

void SortedMultiMap::add(TKey c, TValue v) {
	if (this->firstEmpty == this->m) {
		// the hash table is full so we have to resize it
		this->resizeHashTable();
	}

	this->nrElems++;
	int pos = this->hashF(c);  // the position in the hash table where the element should be added

	if (this->keyInfo[pos] == c) {
		// the key is already in the hash table so we have to add the new value in the dynamic vector

		this->hashTable[pos].values[this->hashTable[pos].sizeV] = v;
		this->hashTable[pos].sizeV++;

		// resize the dynamic vector if it is full
		if (this->hashTable[pos].sizeV == this->hashTable[pos].capacityV) {
			this->resizeValues(pos);
		}
	}
	else if (this->keyInfo[pos] == NULL_TKEY) {
		// the position is empty

		this->keyInfo[pos] = c; // add the key in the hash table
		this->next[pos] = -1;

		if (pos == this->firstEmpty) {
			this->changeFirstEmpty();
		}

		// add the value v in the dynamic vector from hashTable
		this->hashTable[pos].values[this->hashTable[pos].sizeV] = v;
		this->hashTable[pos].sizeV++;

		// resize the dynamic vector if it is full
		if (this->hashTable[pos].sizeV == this->hashTable[pos].capacityV) {
			this->resizeValues(pos);
		}
	}
	else {
		// the position is not empty so we have to find the next empty position starting from pos

		int current = pos;
		while (this->next[current] != -1) {
			current = this->next[current];
		}

		if (this->next[current] == -1) {
			// add the element at the end of the list
			this->keyInfo[this->firstEmpty] = c;
			this->next[this->firstEmpty] = -1;
			this->next[current] = this->firstEmpty;
			this->changeFirstEmpty();
		}

		// add the value v in the dynamic vector from hashTable
		this->hashTable[pos].values[this->hashTable[pos].sizeV] = v;
		this->hashTable[pos].sizeV++;

		// resize the dynamic vector if it is full
		if (this->hashTable[pos].sizeV == this->hashTable[pos].capacityV) {
			this->resizeValues(pos);
		}
	}
}
// BC = Theta(1) - the key is already in the hash table - just add the value
// TC = O(2*m + cap) - the position is not empty - we have to find the next empty position starting from pos
// WC = Theta(2*m + cap) - the position is empty - we have to add the element at the end of the list + change first empty + resize values
// m = capacity of the hash table
// cap = capacity of the dynamic array for each unique key in the hash table

vector<TValue> SortedMultiMap::search(TKey c) const {

	int pos = this->hashF(c);
	vector<TValue> result;  // the vector of values that have the key c

	if (pos >= this->m || pos < 0) {
		// the key c is not in the hash table
		return result;
	}

	if (this->keyInfo[pos] == c) {
		// the key c is in the hash table at the position given by the hash function
		for (int i = 0; i < this->hashTable[pos].sizeV; i++) {
			result.push_back(this->hashTable[pos].values[i]);
		}
	}
	else {
		// the key c is in the table but it is at another position starting from pos
		int current = pos;
		while (this->next[current] != -1 && this->keyInfo[current] != c) {
			current = this->next[current];
		}
		// current is the position of the key c in the hash table
		if (this->next[current] != -1) {
			for (int i = 0; i < this->hashTable[this->next[current]].sizeV; i++) {
				result.push_back(this->hashTable[this->next[current]].values[i]);
			}
		}
	}

	return result;
}
// BC = Theta(1) - the key c is in the hash table at the position given by the hash function
// TC = O(m) - the key c is in the table but it is at another position starting from pos
// WC = Theta(m) - the key c is in the table but it is at another position starting from pos

/*
bool SortedMultiMap::remove(TKey c, TValue v) {

	int pos = this->hashF(c);
	int prevpos = -1; // the position of the previous element in the list

	// search for the key c in the hash table
	while (pos != -1 && this->keyInfo[pos] != c) {
		prevpos = pos;
		pos = this->next[pos];
	}

	if (pos == -1) {
		// the key c is not in the hash table
		return false;
	}
	else {
		// the key c is in the hash table

		this->nrElems--;

		bool hashes = false; // true if the element was removed and the next element was moved to the current position
		do {
			int p = this->next[pos];  // the position of the element in the list
			int prevp = pos;

			while (p != -1 && this->hashTable[pos].values[p] != v) {
				prevp = p;
				p = this->next[p];
			}

			if (p == -1) {
				hashes = true;
			}
			else {
				// move the element from p to pos
				this->keyInfo[pos] = this->keyInfo[p];
				prevpos = prevp;
				pos = p;

				this->hashTable[pos].values[p] = NULL_TVALUE;
				this->hashTable[pos].sizeV--;

				// move the next element to the current position
				if (this->next[p] != -1) {
					this->hashTable[pos].values[p] = this->hashTable[pos].values[this->next[p]];
					this->next[p] = this->next[this->next[p]];
				}
				else {
					this->next[prevp] = -1;
				}
			}
		}
		while (hashes == false);

		// we remove the element from pos (no elem hashes to it)
		if (prevpos == -1) {

			int index = 0;
			while (index < this->m && prevpos == -1) {
				if (this->next[index] == pos) {
					prevpos = index;
				}
				else {
					index++;
				}
			}
		}
		else {
			// the element is not the first in the list
			this->next[prevpos] = this->next[pos];
		}
		this->keyInfo[pos] = NULL_TKEY;
		this->next[pos] = -1;

		this->hashTable[pos].sizeV = 0;
		this->hashTable[pos].capacityV = 10;
		for (int i = 0; i < this->hashTable[pos].sizeV; i++) {
			this->hashTable[pos].values[i] = NULL_TVALUE;
		}

		//this->nrElems--;
		if (pos < this->firstEmpty) {
			this->firstEmpty = pos;
		}

		return true;
	}
}
*/

bool SortedMultiMap::remove(TKey c, TValue v) {
	int pos = this->hashF(c);
	int prevPos = -1; // the position of the previous element in the list

	// search for the key c in the hash table
	while (pos != -1 && this->keyInfo[pos] != c) {
		prevPos = pos;
		pos = this->next[pos];
	}

	if (pos == -1) {
		// the key c is not in the hash table
		return false;
	}
	else {
		// the key c is in the hash table
		bool valueFound = false;  // true if the value v was found in the dynamic array
		int valueIndex = -1;      // the position of the value v in the dynamic array

		// search for the value v in the dynamic array at pos
		for (int i = 0; i < this->hashTable[pos].sizeV; i++) {
			if (this->hashTable[pos].values[i] == v) {
				valueFound = true;
				valueIndex = i;
				break;
			}
		}

		if (!valueFound) {
			// the value v is not in the dynamic array
			return false;
		}
		else {
			// the value v is in the dynamic array
			this->nrElems--;
			// remove the value v from the dynamic array
			for (int i = valueIndex; i < this->hashTable[pos].sizeV - 1; i++) {
				this->hashTable[pos].values[i] = this->hashTable[pos].values[i + 1];
			}
			this->hashTable[pos].sizeV--;

			if (this->hashTable[pos].sizeV == 0) {
				// if the dynamic array is empty remove the key from the hash table

				if (prevPos == -1) {
					// if pos is the head of the list
					int nextPos = this->next[pos];  // the position of the next element in the list

					if (nextPos == -1) {
						// if there is no next element chained to pos remove the key from the hash table
						this->keyInfo[pos] = NULL_TKEY;
						this->hashTable[pos].sizeV = 0;
						this->hashTable[pos].capacityV = 10;

						delete[] this->hashTable[pos].values;
						this->hashTable[pos].values = new TValue[10];

						for (int i = 0; i < 10; i++) {
							this->hashTable[pos].values[i] = NULL_TVALUE;
						}
						this->next[pos] = -1;

					}
					else {
						// if pos is chained to other elements we move the next element to the current position
						this->keyInfo[pos] = this->keyInfo[nextPos];

						this->hashTable[pos].sizeV = this->hashTable[nextPos].sizeV;
						this->hashTable[pos].capacityV = this->hashTable[nextPos].capacityV;

						delete[] this->hashTable[pos].values;
						this->hashTable[pos].values = this->hashTable[nextPos].values;

						this->next[pos] = this->next[nextPos];
						this->next[nextPos] = -1;
						this->keyInfo[nextPos] = NULL_TKEY;
					}
				}
				else {
					// if pos is not the head of the list remove it from the list
					this->next[prevPos] = this->next[pos];
					this->keyInfo[pos] = NULL_TKEY;
					this->next[pos] = -1;

					delete[] this->hashTable[pos].values;
					this->hashTable[pos].values = new TValue[10];
					for (int i = 0; i < 10; i++) {
						this->hashTable[pos].values[i] = NULL_TVALUE;
					}
					this->hashTable[pos].sizeV = 0;
					this->hashTable[pos].capacityV = 10;
				}

				if (pos < this->firstEmpty) {
					// if pos is smaller than first empty update the first empty position
					this->firstEmpty = pos;
				}
			}

			return true;
		}
	}
}
// BC = Theta(size) - c first in the hash table, v first in the dynamic array and only the value v is removed
// TC = O(m * size^2 * cap) - c last in the hash table, v last in the dynamic array and all the values are removed so the key is removed from the hash table
// WC = Theta(m * size^2 * cap) - c last in hash table, v last in dynamic array and all the values are removed so the key is removed from the hash table
// m = capacity of the hash table
// size = the size of the dynamic array for each unique key in the hash table
// cap = capacity of the dynamic array for each unique key in the hash table

int SortedMultiMap::size() const {
	return this->nrElems;
}
// BC = TC = WC = Theta(1)

bool SortedMultiMap::isEmpty() const {
	if (this->nrElems == 0) {
		return true;
	}
	else {
		return false;
	}
}
// BC = TC = WC = Theta(1)

int SortedMultiMap::trimValues(int maxSize) {
	if (maxSize < 1) {
		throw exception();
	}
	int removed = 0;
	for (int i = 0; i < this->m; i++) {
		if (this->hashTable[i].sizeV > maxSize) {
			removed += this->hashTable[i].sizeV - maxSize;
			this->hashTable[i].sizeV = maxSize;
		}
	}
	return removed;
}
// BC = TC = WC = Theta(m) - the capacity of the hash table

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
// BC = TC = WC = Theta(1)

SortedMultiMap::~SortedMultiMap() {
	for (int i = 0; i < this->m; i++) {
		delete[] this->hashTable[i].values;
	}

	delete[] this->hashTable;
	delete[] this->next;
	delete[] this->keyInfo;
}
// BC = TC = WC = Theta(m)
