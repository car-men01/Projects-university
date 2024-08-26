#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
#define NULL_TKEY -111111
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
	friend class SMMIterator;
private:

	/// the dynamic array for each unique key in the hash table
	struct TableKeyValue {
		TValue* values;
		int sizeV;
		int capacityV;
	};

	// multi map using a hashtable with coalesced chaining
	TableKeyValue* hashTable;

	// dynamic arrays for the next and key information
	int* next;
	TKey* keyInfo;

	// the number of slots in the hash table - the capacity of the hash table
	int m;
	int firstEmpty;

	// the number of key - value pairs
	int nrElems;

	// the relation used to order the keys (in iterator)
	Relation relation;

	// returns the position of the key in the hash table
	int hashF(TKey k) const;

	void resizeHashTable();
	void changeFirstEmpty();
	void resizeValues(int pos);

	

public:

	// constructor
	SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
	void add(TKey c, TValue v);

	//returns the values belonging to a given key
	vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
	bool remove(TKey c, TValue v);

	//returns the number of key-value pairs from the sorted multimap
	int size() const;

	//verifies if the sorted multi map is empty
	bool isEmpty() const;

	// returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
	SMMIterator iterator() const;

	//limits the number of values for a key to maxSize.
	//From the keys with more than maxSize values, some values (does not matter which ones) will be
	//removed until the number of associated values will be equal to maxSize.
	//If a key has less than maxSize values, nothing will be changed for that key.
	//The limitation foes not have to be respected after the call to the function (so new pairs can be added).
	//Returns the number of removed pairs.
	int trimValues(int maxSize);

	// destructor
	~SortedMultiMap();
};
