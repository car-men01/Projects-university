#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include <iostream>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());

    // test trimValues
    for (int i = 0; i < 10; i++) {
		smm.add(1, i);
	}
    for (int i = 0; i < 7; i++) {
        smm.add(2, i);
    }
    for (int i = 0; i < 5; i++) {
		smm.add(3, i);
	}
    
    smm.trimValues(6);

    v = smm.search(1);
    assert(v.size() == 6);
    v = smm.search(2);
    assert(v.size() == 6);
    v = smm.search(3);
    assert(v.size() == 5);

    smm.trimValues(1);
    v = smm.search(1);
    assert(v.size() == 1);

    try {
        smm.trimValues(0);
        assert(false);
    }
    catch (exception e) {
		assert(true);
	}

    cout << "tested trimValues" << endl;

}

