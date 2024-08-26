#pragma once
#include "Dog.h"
#include "Repository.h"
#include "AdoptionList.h"
#include "FileAdoptionList.h"
#include "RepoExceptions.h"
#include <string>
#include <vector>
#include <algorithm>
#include <map>

class Service
{
private:
	Repository repo;
	AdoptionList* adoption_list;

public:
	Service(const Repository& repo);
	Service(const Repository& repo, AdoptionList* adoption_list);

	Service& operator=(const Service& service);

	~Service();

	void add(const std::string& breed, const std::string& name, int age, const std::string& photo);
	void remove(const std::string& breed, const std::string& name);
	void update(const std::string& breed, const std::string& name, int age, const std::string& photo);

	std::vector<Dog> get_by_breed_and_age(int age, const std::string& breed);
	std::map<std::string, int> get_by_breed();
	std::vector<Dog> get_all();

	AdoptionList* get_all_adopted();
	void add_to_adopted(const Dog& dog);
	void remove_from_adopted(const std::string& breed, const std::string& name);
	void updateAdoptionList(FileAdoptionList* newl);

	void show_adoption_list();
	void next_adoption_list();
	void save_adoption_list();
	void open_adoption_list();

	int check_name_and_breed(const std::string& breed, const std::string& name);

	void add_generated_dogs();

};

