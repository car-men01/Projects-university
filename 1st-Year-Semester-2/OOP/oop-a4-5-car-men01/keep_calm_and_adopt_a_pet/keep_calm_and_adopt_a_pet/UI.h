#pragma once
#include "dog.h"
#include "dynamic_array.h"
#include "repository.h"
#include "service.h"
#include "tests.h"

class UI
{
private:
	Service service = Service();

public:
	UI();
	UI(const Service& service);

	UI& operator=(const UI& ui);

	~UI();

	void add_ui(const std::string& breed, const std::string& name, int age, const std::string& photo);
	void remove_ui(const std::string& breed, const std::string& name);
	void update_ui(const std::string& breed, const std::string& name, int age, const std::string& photo);

	void display_all();
	void print_starting_menu();
	void print_menu_admin();
	void print_menu_user();

	void run();
};

