#pragma once
#include "dog.h"
#include "dynamic_array.h"

class Repository
{
private:
	//DynamicArray dogs = DynamicArray();

	DynamicVector<Dog> dogs;
	
public:
	Repository();
	Repository(const Repository& repo);

	Repository& operator=(const Repository& repo);

	~Repository();

	void add_repo(const Dog& dog);
	void remove_repo(int index);
	void update_repo(const Dog& dog, int index);

	int get_size();

	DynamicVector<Dog> get_all_repo();

};
