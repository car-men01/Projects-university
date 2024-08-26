#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>
#include <exception>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

	// test addOccurences

	sb.addOccurences(3, 5);
	assert(sb.size() == 8);
	assert(sb.nrOccurrences(5) == 4);

	try {
		sb.addOccurences(-1, 5);
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}

	sb.addOccurences(2, 7);
	assert(sb.size() == 10);

	std::cout << "Testes addOccurences" << std::endl;

}

