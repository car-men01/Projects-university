#pragma once
#include "dog.h"
#include "dynamic_array.h"
#include "repository.h"

class Service
{
private:
	Repository repo = Repository();
	
public:
	Service();
	Service(const Repository& repo);

	Service& operator=(const Service& service);

	~Service();

	void add(const std::string& breed, const std::string& name, int age, const std::string& photo);
	void remove(const std::string& breed, const std::string& name);
	void update(const std::string& breed, const std::string& name, int age, const std::string& photo);
	
	DynamicVector<Dog> get_all();
	int check_name_and_breed(const std::string& breed, const std::string& name);

	void add_generated_dogs();

};

