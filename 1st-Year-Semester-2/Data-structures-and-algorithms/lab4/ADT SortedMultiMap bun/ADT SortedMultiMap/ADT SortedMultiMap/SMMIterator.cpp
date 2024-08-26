#include "SMMIterator.h"
#include "SortedMultiMap.h"

#include <iostream>

/*
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){

    // Create a vector of (key, dynamic array of values) pairs
    //for (int i = 0; i < d.m; ++i) {
    //    int current = i;
    //    while (current != -1) {
    //        TKey key = d.keyInfo[current];
    //        for (int j = 0; j < d.hashTable[current].sizeV; j++) {
    //            this->elements.push_back(make_pair(key, d.hashTable[current].values[j]));
    //        }
    //        current = d.next[current];
    //    }
    //}

    //// cout << "size of elements: " << this->elements.size() << endl;

    ////// Sort the elements vector using the given relation
    ////sort(this->elements.begin(), this->elements.end(), [&](const TElem& a, const TElem& b) {
    ////    return d.relation(a.first, b.first);
    ////    });


    this->currentElement = 0;
    // mergem prima data pe keyinfo si facem un vector crescator cu cheile
    TKey* keys = new TKey[d.m];
    int nrkeys = 0;
    for(int i = 0; i < d.m; i++){
        if (d.keyInfo[i] != NULL_TKEY) {
            int j = 0;
            Relation rel = d.relation;
            while (j < i && rel(d.keyInfo[i], keys[j])) {
				j++;
			}
            for (int k = i; k > j; k--) {
				keys[k] = keys[k - 1];
			}
			keys[j] = d.keyInfo[i];
            nrkeys++;
		}
	}
    int elemente = 0;
    for (int i = 0; i < nrkeys; i++) {
        int current = keys[i];
        int pos = d.hashF(current);
        for (int j = 0; j < d.hashTable[pos].sizeV; j++) {
            this->elements.push_back(make_pair(pos, d.hashTable[pos].values[j]));
            elemente++;
		}
	}
    cout << "elemente: " << elemente << "  nrElemente din m:  "<< d.nrElems << endl;
}
*/

/*
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->currentElement = 0;

    // Create an array to store keys in sorted order
    TKey* keys = new TKey[d.m];
    int nrkeys = 0;

    // Collect keys and sort them
    for (int i = 0; i < d.m; i++) {
        if (d.keyInfo[i] != NULL_TKEY) {
            int j = nrkeys - 1;
            // Find the correct position to insert the current key
            while (j >= 0 && d.relation(d.keyInfo[i], keys[j])) {
                keys[j + 1] = keys[j];
                j--;
            }
            keys[j + 1] = d.keyInfo[i];
            nrkeys++;
        }
    }

    // Collect and store elements based on sorted keys
    for (int i = 0; i < nrkeys; i++) {
        TKey key = keys[i];
        int current = d.hashF(key);
        while (current != -1 && d.keyInfo[current] != key) {
            current = d.next[current];
        }
        if (current != -1) {
            for (int j = 0; j < d.hashTable[current].sizeV; j++) {
                this->elements.push_back(make_pair(key, d.hashTable[current].values[j]));
            }
        }
    }

    delete[] keys;

    // Optional: Print the number of elements
    cout << "elemente: " << this->elements.size() << "  nrElemente din m: " << d.nrElems << endl;
}

*/


/*
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->currentElement = 0;

    // Create an array to store keys
    TKey* keys = new TKey[d.m];
    int nrkeys = 0;

    // First collect all keys in the array

    for (int i = 0; i < d.m; i++) {
        if (d.keyInfo[i] != NULL_TKEY) {
			keys[nrkeys] = d.keyInfo[i];
			nrkeys++;
		}
	}

    // sort the keys selection sort
    for (int i = 0; i < nrkeys - 1; i++) {
        for (int j = i + 1; j < nrkeys; j++) {
            if (d.relation(keys[i], keys[j])) {
				TKey aux = keys[i];
				keys[i] = keys[j];
				keys[j] = aux;
			}
		}
	}

	// Collect and store elements based on sorted keys
    for (int i = 0; i < nrkeys; i++) {
		TKey key = keys[i];
		int current = d.hashF(key);
        if (d.keyInfo[current] != key) {
            while (current != -1 && d.keyInfo[current] != key) {
                current = d.next[current];
            }
        }
        //if (current != -1) {
        if (d.keyInfo[current] != NULL_TKEY) {
            this->elements.push_back(make_pair(key, d.hashTable[current].values);
            for (int j = 0; j < d.hashTable[current].sizeV; j++) {
                this->elements.push_back(make_pair(key, d.hashTable[current].values[j]));
            }
       
		}
	}

	delete[] keys;

	// Optional: Print the number of elements
	std::cout << "elemente: " << this->elements.size() << "  nrElemente din m: " << d.nrElems << endl;
}
*/


/*
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->currentElement = 0;

    // Create an array to store keys
    vector<TKey> keys;

    // First, collect all keys
    for (int i = 0; i < d.m; ++i) {
        
        if (d.keyInfo[i] != NULL_TKEY) {
            cout << " i " << i << ",  keyInfo " << d.keyInfo[i] << endl;
            keys.push_back(d.keyInfo[i]);
        }
    }

    // Sort the keys using the given relation
    sort(keys.begin(), keys.end(), d.relation);

    // Collect and store elements based on sorted keys
    for (TKey key : keys) {
        int current = d.hashF(key);

        // Traverse the chain to find the key
        while (current != -1 && d.keyInfo[current] != key) {
            current = d.next[current];
        }

        // If the key is found, collect all its values
        if (current != -1 && d.keyInfo[current] == key) {
            vector<TValue> values;
            for (int j = 0; j < d.hashTable[current].sizeV; ++j) {
                values.push_back(d.hashTable[current].values[j]);
            }
            this->elements.push_back(make_pair(key, values));
        }
    }

    // Optional: Print the number of elements for debugging
    cout << "elemente: " << this->elements.size() << ", nrElemente din m: " << d.nrElems << endl;
}
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    this->currentElement = 0;
    vector<TKey> keys;

    // collect all keys
    for (int i = 0; i < d.m; ++i) {
        if (d.keyInfo[i] != NULL_TKEY) {
            keys.push_back(d.keyInfo[i]);
        }
    }

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
}
//// BC = Theta(m + sizeK * sizeV) - the keys are already sorted
//// TC = Theta(m + sizeK * sizeV + sizeK^2) - the keys are not sorted
//// WC = Theta(m + sizeK * sizeV + sizeK^2) - the keys are not sorted
//// m = capacity of the hash table, sizeK = size of keys vector, sizeV = size of values vector

void SMMIterator::first(){
	this->currentElement = 0;
}
//// BC = WC = TC = Theta(1)


void SMMIterator::next(){

    if (!this->valid()) {
        throw exception();
    }

    this->currentElement++;
}
//// BC = WC = TC = Theta(1)


bool SMMIterator::valid() const{

    int size = 0;
    for (auto& pair : this->elements) {
		size += pair.second.size();
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


TElem SMMIterator::getCurrent() const {

    if (!this->valid()) {
        throw exception();
    }

    int c = 0;
    for (auto elem : this->elements) {
        for (auto val : elem.second) {
            if (c == this->currentElement) {
                return make_pair(elem.first, val);
            }
            c++;
        }
    }

}
// BC = TC = WC = Theta(sizeEl * sizeV) 
// sizeEl = size of elements vector - number of (key, dynamic array of values) pairs
// sizeV = size of values vector
