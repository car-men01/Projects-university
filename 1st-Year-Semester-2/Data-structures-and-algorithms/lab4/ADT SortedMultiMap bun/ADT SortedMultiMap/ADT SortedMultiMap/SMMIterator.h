#pragma once

#include "SortedMultiMap.h"

#include <algorithm>
#include <vector>
/*ypedef int TKey;

typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);*/

using namespace std;

class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	int currentElement;

	struct TableKeyValue {
		TValue* values;
		int sizeV;
		int capacityV;
	};
	vector<pair<TKey, vector<TValue>>> elements;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

