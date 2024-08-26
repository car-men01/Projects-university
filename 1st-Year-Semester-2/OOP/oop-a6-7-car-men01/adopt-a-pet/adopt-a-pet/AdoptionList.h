#pragma once
#include <vector>
#include "Dog.h"

using std::vector;

class AdoptionList
{
protected:
	vector <Dog> dogs;
	int current;

public:
	AdoptionList();
	virtual ~AdoptionList();

	Dog getCurrentDog();
	vector <Dog> getDogs();

	void add(const Dog& d);
	void remove(int pos);

	void show();
	void next();
	int size();
	bool isEmpty();
	
};

