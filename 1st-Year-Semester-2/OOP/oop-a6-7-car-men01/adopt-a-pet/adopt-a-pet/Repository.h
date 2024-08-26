#pragma once
#include "Dog.h"
#include <vector>

using std::vector;
using std::string;

class Repository
{
private:
	vector<Dog> dogs;
	vector<Dog> adoption_list;
	string filename;

public:
	Repository(const std::string& filename);
	~Repository();

	Dog find_by_breed_and_name(const string& breed, const string& name) const;

	void add_repo(Dog dog);
	void remove_repo(int index);
	void update_repo(Dog dog, int index);

	void add_adoption_list(Dog d);
	void remove_adoption_list(int index);

	int get_size();

	vector<Dog> get_all_repo();
	vector<Dog> get_adoption_list();
	Dog get_dog(int index);

	void readFromFile();
	void writeToFile();
};
