#pragma once
#include "Set.h"

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	const Set& set;

	Set::SLLNode* current;



	SetIterator(const Set& s);

	

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;

	// changes the current element from the iterator to the previous element
	// or if the current element was first, makes the iterator invalid
	// throws an exception if the iterator is not valid
	void previous();
};


