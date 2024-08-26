#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;

	int currKey;
	int currValue;

	//DO NOT CHANGE THIS PART
	MultiMapIterator(const MultiMap& c);

public:
	TElem getCurrent()const;
	bool valid() const;
	void next();
	void first();

	//moves the current element from the iterator k steps forward, 
	//or makes the iterator invalid if there are less than k elements left
	void jumpForward(int k);
};

