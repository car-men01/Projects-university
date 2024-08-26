#pragma once

#include "SortedMultiMap.h"

#include <algorithm>
#include <vector>

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

		/*void addValue(TValue value) {
			if (sizeV == capacityV) {
				// resize the array if needed
				capacityV *= 2;
				TValue* newValues = new TValue[capacityV];
				for (int i = 0; i < sizeV; ++i) {
					newValues[i] = values[i];
				}
				delete[] values;
				values = newValues;
			}

			values[sizeV] = value;
			sizeV++;
			
		}
		*/

	};
	vector<pair<TKey, vector<TValue>>> elements;
	//vector<pair<TKey, TableKeyValue*>> elements;

	//void addValue(TValue value);

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

