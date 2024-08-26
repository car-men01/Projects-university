#include "SMMIterator.h"
#include "SortedMultiMap.h"

#include <iostream>

using namespace std;

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->currentElement = 0;

    // create an array to store keys
    vector<TKey> keys;

    // collect all keys
    for (int i = 0; i < d.m; ++i) {
        if (d.keyInfo[i] != NULL_TKEY) {
            keys.push_back(d.keyInfo[i]);
        }
    }
    
    // sort the keys array based on the given relation
    for (int i = 0; i < keys.size() - 1; i++) {
        for (int j = i + 1; j < keys.size(); j++) {
            if (!d.relation(keys[i], keys[j])) {
                TKey aux = keys[i];
                keys[i] = keys[j];
                keys[j] = aux;
            }
        }
    }

    // collect and store elements based on sorted keys
    for (TKey key : keys) {
        int current = d.hashF(key);

        // find the key
        while (current != -1 && d.keyInfo[current] != key) {
            current = d.next[current];
        }

        // if the key is found, collect all its values
        if (current != -1 && d.keyInfo[current] == key) {
            vector<TValue> values;
            for (int j = 0; j < d.hashTable[current].sizeV; ++j) {
                values.push_back(d.hashTable[current].values[j]);
            }
            this->elements.push_back(make_pair(key, values));
        }
    }
    
    /*
    this->currentElement = 0;

    // Create an array to store keys
    vector<TKey> keys;

    // Collect all keys
    for (int i = 0; i < d.m; ++i) {
        if (d.keyInfo[i] != NULL_TKEY) {
            keys.push_back(d.keyInfo[i]);
        }
    }

    // Sort the keys array based on the given relation
    for (int i = 0; i < keys.size() - 1; i++) {
        for (int j = i + 1; j < keys.size(); j++) {
            if (!d.relation(keys[i], keys[j])) {
                TKey aux = keys[i];
                keys[i] = keys[j];
                keys[j] = aux;
            }
        }
    }

    // Collect and store elements based on sorted keys
    for (TKey key : keys) {
        int current = d.hashF(key);

        // Find the key
        while (current != -1 && d.keyInfo[current] != key) {
            current = d.next[current];
        }

        // If the key is found, collect all its values
        if (current != -1 && d.keyInfo[current] == key) {
            TableKeyValue* tableKeyValue = new TableKeyValue[d.hashTable[current].capacityV];
            for (int j = 0; j < d.hashTable[current].sizeV; ++j) {
                
                tableKeyValue->addValue(d.hashTable[current].values[j]);
            }
            this->elements.push_back(make_pair(key, tableKeyValue));
        }
    }
    */
}
// BC = Theta(m + sizeK * sizeV) - the keys are already sorted
// TC = Theta(m + sizeK * sizeV + sizeK^2) - the keys are not sorted
// WC = Theta(m + sizeK * sizeV + sizeK^2) - the keys are not sorted
// m = capacity of the hash table, sizeK = size of keys vector, sizeV = size of values vector


void SMMIterator::first(){
	this->currentElement = 0;
}
// BC = WC = TC = Theta(1)

void SMMIterator::next(){

    if (!this->valid()) {
        throw exception();
    }

    this->currentElement++;
}
// BC = WC = TC = Theta(1)

bool SMMIterator::valid() const{

    int size = 0;
    for (auto elem : this->elements) {
		size += elem.second.size();
        //size += elem.second->sizeV;
	}
    if (this->currentElement >= size) {
		return false;
	}
    else {
        return true;
    }
}
// BC = TC = WC = Theta(sizeEl)
// sizeEl = size of elements vector - number of (key, dynamic array of values) pairs

TElem SMMIterator::getCurrent() const{

    if (!this->valid()) {
		throw exception();
	}

    int c = 0;
    for (auto elem : this->elements) {
        /*for (auto val : elem.second) {
            if (c == this->currentElement) {
                return make_pair(elem.first, val);
            }
            c++;
        }*/
        for (int i = 0; i < elem.second->sizeV; i++) {
            if (c == this->currentElement) {
				return make_pair(elem.first, elem.second->values[i]);
			}
			c++;
		}
    }
}
// BC = TC = WC = Theta(sizeEl * sizeV) 
// sizeEl = size of elements vector - number of (key, dynamic array of values) pairs
// sizeV = size of values vector
