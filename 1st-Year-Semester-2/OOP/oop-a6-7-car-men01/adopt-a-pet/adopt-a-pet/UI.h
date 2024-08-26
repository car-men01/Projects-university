#pragma once
#include "Dog.h"
#include "Repository.h"
#include "Service.h"
#include <vector>

class UI
{
private:
	Service service;

public:
	UI(const Service& service);

	UI& operator=(const UI& ui);

	~UI();

	void add_ui(const std::string& breed, const std::string& name, int age, const std::string& photo);
	void remove_ui(const std::string& breed, const std::string& name);
	void update_ui(const std::string& breed, const std::string& name, int age, const std::string& photo);

	void save_adoption_list_to_file();

	void display_all();
	void print_starting_menu();
	void print_menu_admin();
	void print_menu_user();

	void run();
};

