#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

using std::cout;

MultiMap::MultiMap() {

	this->capacity = 10;
	this->nodes = new DLLANode[this->capacity];

    // link the nodes
	for (int i = 0; i < this->capacity - 1; i++) {
		this->nodes[i].next = i + 1;
		this->nodes[i + 1].prev = i;
	}

	this->nodes[capacity - 1].next = -1; // last node
    this->nodes[0].prev = -1; // first node

    this->head = -1;
    this->tail = -1;
    this->firstEmpty = 0;
    this->nrELems = 0;
}
// BC = TC = WC = Theta(n), n = capacity


void MultiMap::add(TKey c, TValue v) {
	
    // check if the key already exists
    int keyIndex = -1;
    int current = this->head;

    while (current != -1) {

        if (this->nodes[current].keyInfo == c) {
			keyIndex = current;
			break;
		}
		current = this->nodes[current].next;
	}

    if (keyIndex != -1) {
        // key already exists so we add the value to its DLLA
        DLLASmall& dlla = *this->nodes[keyIndex].info;

        if (dlla.firstEmptyS == -1) {

            // resize the array if it's full
            int newCapacity = dlla.capacityS * 2;
            DLLANodeSmall* newNodes = new DLLANodeSmall[newCapacity];
            for (int i = 0; i < dlla.capacityS; ++i) {
                newNodes[i] = dlla.nodesS[i];
            }

            // link the new elements
            for (int i = dlla.capacityS; i < newCapacity; i++) {
                newNodes[i].prevS = i - 1;

                if (i + 1 < newCapacity) {
                    newNodes[i].nextS = i + 1;
                }
                else {
                    newNodes[i].nextS = -1;
                }
            }

            delete[] dlla.nodesS;
            dlla.nodesS = newNodes;
            // set the first empty slot to the end of the resized array
            dlla.firstEmptyS = dlla.capacityS + 1; 
            dlla.capacityS = newCapacity;
        }

        // add the value to the DLLA
        int emptyIndex = dlla.firstEmptyS;

        if (dlla.tailS != -1) {
            dlla.nodesS[dlla.tailS].nextS = emptyIndex;
        }

        // update the first empty slot
        dlla.firstEmptyS = dlla.nodesS[emptyIndex].nextS;
        // add the value
        dlla.nodesS[emptyIndex].infoS = v;
        dlla.nodesS[emptyIndex].nextS = -1;
        dlla.nodesS[emptyIndex].prevS = dlla.tailS;

        if (dlla.headS == -1) {
            dlla.headS = emptyIndex;
        }

        dlla.tailS = emptyIndex;
        dlla.nrELemsS++;

    }
    else {
        // key does not exist, create a new DLLA for the key and add the value
        if (firstEmpty == -1) {

            // resize the array if it's full
            int newCapacity = capacity * 2;
            DLLANode* newNodes = new DLLANode[newCapacity];
            for (int i = 0; i < capacity; ++i) {
                newNodes[i] = nodes[i];
            }

            // link the new elements
            for (int i = capacity; i < newCapacity; ++i) {
                newNodes[i].prev = i - 1;

                if (i + 1 < newCapacity) {
                    newNodes[i].next = i + 1;
                }
                else {
                    newNodes[i].next = -1;
                }
            }

            delete[] nodes;
            nodes = newNodes;
            // set the first empty slot to the end of the resized array
            firstEmpty = capacity + 1; 
            capacity = newCapacity;
        }

        // add the key to the array
        int emptyIndex = firstEmpty;
        firstEmpty = nodes[emptyIndex].next;
        nodes[emptyIndex].keyInfo = c;

        // create a new DLLASmall for the key
        nodes[emptyIndex].info = new DLLASmall();
        nodes[emptyIndex].info->capacityS = 10;
        nodes[emptyIndex].info->nodesS = new DLLANodeSmall[10]; 
        
        // link the nodes in the new DLLASmall array
        for (int i = 0; i < 9; i++) {
			nodes[emptyIndex].info->nodesS[i].nextS = i + 1;
			nodes[emptyIndex].info->nodesS[i + 1].prevS = i;
		}

        nodes[emptyIndex].info->nodesS[9].nextS = -1; // last node
        nodes[emptyIndex].info->nodesS[0].prevS = -1; // first node

        nodes[emptyIndex].info->headS = -1;
        nodes[emptyIndex].info->tailS = -1;
        nodes[emptyIndex].info->firstEmptyS = 0;
        nodes[emptyIndex].info->nrELemsS = 0;

        // add the value to the new DLLA
        int emptyIndexS = nodes[emptyIndex].info->firstEmptyS;
        nodes[emptyIndex].info->firstEmptyS = nodes[emptyIndex].info->nodesS[emptyIndexS].nextS;
        nodes[emptyIndex].info->nodesS[emptyIndexS].infoS = v;

        nodes[emptyIndex].info->nodesS[emptyIndexS].nextS = -1;
        nodes[emptyIndex].info->nodesS[emptyIndexS].prevS = -1;
        nodes[emptyIndex].info->headS = emptyIndexS;
        nodes[emptyIndex].info->tailS = emptyIndexS;
        nodes[emptyIndex].info->nrELemsS++;

        if (nodes[emptyIndex].info->headS == -1) {
			nodes[emptyIndex].info->headS = emptyIndexS;
		}
        
        nodes[emptyIndex].info->tailS = emptyIndexS;

        nodes[emptyIndex].next = -1;
        nodes[emptyIndex].prev = tail;

        if (this->head == -1) {
            this->head = emptyIndex;
        }
        else {
            this->nodes[tail].next = emptyIndex;
        }
        this->tail = emptyIndex;

    }

    this->nrELems++;
}
// BC = Theta(1), WC = Theta(n + 2m)
// TC = O(n + 2m), n = nrElems, m = capacityS


bool MultiMap::remove(TKey c, TValue v) {

    // check if the key already exists
    int keyIndex = -1;
    int current = this->head;

    while (current != -1) {

        if (this->nodes[current].keyInfo == c) {
            keyIndex = current;
            break;
        }
        current = this->nodes[current].next;
    }

    if (keyIndex != -1) {
        // key found, search for the value in the array
        DLLASmall& dlla = *this->nodes[keyIndex].info;
        int valueIndex = dlla.headS;

        while (valueIndex != -1) {
            if (dlla.nodesS[valueIndex].infoS == v) {
                // value found, remove it from the array
                if (dlla.nodesS[valueIndex].prevS != -1)
                    dlla.nodesS[dlla.nodesS[valueIndex].prevS].nextS = dlla.nodesS[valueIndex].nextS;
                if (dlla.nodesS[valueIndex].nextS != -1)
                    dlla.nodesS[dlla.nodesS[valueIndex].nextS].prevS = dlla.nodesS[valueIndex].prevS;
                if (dlla.headS == valueIndex)
                    dlla.headS = dlla.nodesS[valueIndex].nextS;
                if (dlla.tailS == valueIndex)
                    dlla.tailS = dlla.nodesS[valueIndex].prevS;

                // link the removed node to the first empty slot
                dlla.nodesS[valueIndex].nextS = dlla.firstEmptyS;
                dlla.firstEmptyS = valueIndex;
                dlla.nrELemsS--;
                this->nrELems--;

                if (dlla.nrELemsS == 0) {
                    // if there are no more elements in the array, update the key's pointers
                    if (this->nodes[keyIndex].prev != -1)
                        this->nodes[this->nodes[keyIndex].prev].next = this->nodes[keyIndex].next;
                    if (this->nodes[keyIndex].next != -1)
                        this->nodes[this->nodes[keyIndex].next].prev = this->nodes[keyIndex].prev;
                    if (this->head == keyIndex)
                        this->head = this->nodes[keyIndex].next;
                    if (this->tail == keyIndex)
                        this->tail = this->nodes[keyIndex].prev;
                    // delete the DLLA and update the first empty slot
                    delete[] dlla.nodesS;
                    delete this->nodes[keyIndex].info;
                    this->nodes[keyIndex].info = nullptr;
                    this->nodes[keyIndex].next = this->firstEmpty;
                    this->firstEmpty = keyIndex;
                }

                return true; // pair removed successfully
            }
            valueIndex = dlla.nodesS[valueIndex].nextS;
        }
    }

    return false; // key or value not found
 	
}
// BC = Theta(1), WC = Theta(n + m)
// TC = O(n + m), n = nrElems, m = nrElemsS


vector<TValue> MultiMap::search(TKey c) const {

    // check if the key exists
    int keyIndex = -1;
    int current = this->head;

    while (current != -1) {

        if (this->nodes[current].keyInfo == c) {
            keyIndex = current;
            break;
        }
        current = this->nodes[current].next;
    }

    vector<TValue> values;

    // if the key exists, add its values to the vector
    if (keyIndex != -1) {
        DLLASmall& dlla = *this->nodes[keyIndex].info;
        int current = dlla.headS;

        // add the values to the vector
        while (current != -1) {
            values.push_back(dlla.nodesS[current].infoS);
            current = dlla.nodesS[current].nextS;
        }
    }

	return values;
}
// BC = Theta(1), WC = Theta(n + m)
// TC = O(n + m), n = nrELems, m = nrELemsS

int MultiMap::size() const {

    return this->nrELems;
}
// BC = TC = WC = Theta(1)


bool MultiMap::isEmpty() const {
	
    if (this->nrELems == 0) {
		return true;
	}
    return false;
}
// BC = TC = WC = Theta(1)


MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}
// BC = TC = WC = Theta(1)


MultiMap::~MultiMap() {

    int current = this->head;
    // delete the DLLASmall arrays
	while (current != -1) {
		if (this->nodes[current].next != -1) {
			delete[] this->nodes[current].info->nodesS;
			delete this->nodes[current].info;
		}
		current = this->nodes[current].next;
	}
    // delete the DLLANode array
    delete[] this->nodes;
}
// BC = TC = WC = O(n), n = capacity
