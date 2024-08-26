#include "UI.h"
#include <iostream>
#include <crtdbg.h>
#include <string>

using namespace std;

UI::UI() {}

UI::UI(const Service& service)
{
	this->service = service;
}

UI& UI::operator=(const UI& ui)
{
	if (this == &ui)
		return *this;
	this->service = ui.service;
	return *this;
}

UI::~UI() {}

void UI::add_ui(const std::string& breed, const std::string& name, const int age, const std::string& photo)
{
	if (this->service.check_name_and_breed(breed, name) == 0) {
		this->service.add(breed, name, age, photo);
		cout << "The dog named " << name << ", breed " << breed << " was added to the shelter successfully!" << endl;
	}
	else {
		cout << "The dog named " << name << ", breed " << breed << " already exists in the shelter!" << endl;
	}
	
}

void UI::remove_ui(const std::string& breed, const std::string& name)
{
	if (this->service.check_name_and_breed(breed, name)) {
		this->service.remove(breed, name);
		cout << "The dog named " << name << ", breed " << breed << " was removed from the shelter successfully!" << endl;
	}
	else {
		cout << "The dog named " << name << ", breed " << breed << " does not exist in the shelter!" << endl;
	}
}

void UI::update_ui(const std::string& breed, const std::string& name, const int age, const std::string& photo)
{
	if (this->service.check_name_and_breed(breed, name)) {
		this->service.update(breed, name, age, photo);
		cout << "The dog named " << name << ", breed " << breed << " was updated successfully!" << endl;
	}
	else {
		cout << "The dog named " << name << ", breed " << breed << " does not exist in the shelter!" << endl;
	}
}

void UI::display_all()
{
	DynamicVector<Dog> dogs = this->service.get_all();
	for (int i = 0; i < dogs.get_size(); i++)
	{
		cout << i + 1 << " - Breed: " << dogs[i].get_breed() << ", Name: " << dogs[i].get_name() 
			<< ", Age: " << dogs[i].get_age() << ", Photo link: " << dogs[i].get_photo() << endl;
	}
}

void UI::print_starting_menu()
{
	cout << "Welcome to the \"Keep calm and adopt a pet!\" shelter" << endl;
	cout << "1. Administrator mode" << endl;
	cout << "2. User mode" << endl;
	cout << "3. Exit the application" << endl;
	cout << endl;
}

void UI::print_menu_admin()
{
	cout << endl << "You are running the application in administrator mode." << endl;
	cout << "1. Add a dog to the shelter" << endl;
	cout << "2. Remove a dog from the shelter (adopt)" << endl;
	cout << "3. Update the information of a dog" << endl;
	cout << "4. Display all dogs from the shelter" << endl;
	cout << "5. Exit the application" << endl;
	cout << endl;
}

void UI::print_menu_user()
{
	cout << endl << "You are running the application in user mode." << endl;
	cout << "1. Display the dogs from the database one by one" << endl;
	//cout << "2. Adopt the dog" << endl;
	//cout << "3. Do not adopt the dog" << endl;
	cout << "2. Display all the dogs of a given breed having the age less than a given number" << endl;
	cout << "3. Display the adoption list" << endl;
	cout << "4. Exit the application" << endl;
	cout << endl;
}

void UI::run()
{
	int option, option_start;
	string breed, name, photo;
	int age;

	this->service.add_generated_dogs();
	DynamicVector<Dog> dogs = this->service.get_all();
	DynamicVector<Dog> adopted_dogs = DynamicVector<Dog>();

	this->print_starting_menu();
	cout << "Enter an option from the starting menu: ";
	cin >> option_start;
	cin.ignore();
	cout << endl;

	if (option_start == 1) {
		while (true)
		{
			this->print_menu_admin();
			cout << "Enter an option: ";
			cin >> option;
			cin.ignore();
			cout << endl;

			if (option == 1) {
				cout << "You are adding a dog to the shelter!" << endl;
				cout << "Enter the breed: ";
				getline(cin, breed);
				cout << "Enter the name: ";
				getline(cin, name);
				cout << "Enter the age: ";
				cin >> age;
				cin.ignore();
				cout << "Enter the photo link: ";
				getline(cin, photo);

				this->add_ui(breed, name, age, photo);
			}

			else if (option == 2) {
				cout << "You are removing a dog from the shelter!" << endl;
				cout << "Enter the breed: ";
				getline(cin, breed);
				cout << "Enter the name: ";
				getline(cin, name);

				this->remove_ui(breed, name);
			}

			else if (option == 3) {
				cout << "You are updating the information of a dog from the shelter!" << endl;
				cout << "Enter the breed: ";
				getline(cin, breed);
				cout << "Enter the name: ";
				getline(cin, name);
				cout << "Enter the new age: ";
				cin >> age;
				cin.ignore();
				cout << "Enter the new photo link: ";
				getline(cin, photo);

				this->update_ui(breed, name, age, photo);
			}

			else if (option == 4) {
				cout << "The dogs in the shelter are: " << endl;
				this->display_all();
			}

			else if (option == 5) {
				cout << "You have exited the application!" << endl;
				break;
			}
			else {
				cout << "Invalid option!" << endl;
			}
		}
	}

	else if (option_start == 2) {
		while (true) {
			this->print_menu_user();
			cout << "Enter an option: ";
			cin >> option;
			cin.ignore();
			cout << endl;

			if (option == 1) {
				int i = 0;

				while (i < dogs.get_size()) {
					cout << "Breed: " << dogs[i].get_breed() << ", Name: " << dogs[i].get_name()
						<< ", Age: " << dogs[i].get_age() << ", Photo link: " << dogs[i].get_photo() << endl;
					cout << "Do you want to adopt this dog? (y/n): ";

					string answer, answer_next;
					getline(cin, answer);

					if (answer == "y") {
						adopted_dogs.add(dogs[i]);
						
						cout << "You adopted " << dogs[i].get_name() << ", breed " << dogs[i].get_breed() << " successfully!" << endl;


						breed = dogs[i].get_breed();
						name = dogs[i].get_name();
						dogs.remove(i);
						this->service.remove(breed, name);
						i--;

						cout << "Do you want to show the next dog? (y/n): ";
						getline(cin, answer_next);

						if (answer_next == "y") {
							i++;

							if (dogs.get_size() == 0) {
								cout << "There are no more dogs in the shelter!" << endl;
								break;
							}

							if (i == dogs.get_size()) {
								i = 0;
							}

							continue;
						} else if (answer_next == "n") {
							break;
						}
						else {
							cout << "Invalid answer, please type y/n!" << endl;
						}
					}
					else if (answer == "n") {
						cout << "You chose not to adopt " << dogs[i].get_name() << ", breed " << dogs[i].get_breed() << "." << endl;

						cout << "Do you want to show the next dog? (y/n): ";
						getline(cin, answer_next);

						if (answer_next == "y") {
							i++;
							if (dogs.get_size() == 0) 
							{
								cout << "There are no more dogs in the shelter!" << endl;
								break;
							}

							if (i == dogs.get_size()) {
								i = 0;
							}
							continue;
						}
						else if (answer_next == "n") {
							break;
						}
						else {
							cout << "Invalid answer, please type y/n!" << endl;
						}
					}
					else {
						cout << "Invalid answer, please type y/n!" << endl;
					}
				}
			}

			else if (option == 2) {
				cout << "Enter the breed: ";
				getline(cin, breed);
				cout << "Enter the age: ";
				cin >> age;
				cin.ignore();

				int ok = 0, i = 0, exists = 0;

				if (breed == "") {
					ok = 1;
				}

				while (i < dogs.get_size()) {

					if (ok == 1) {
						breed = dogs[i].get_breed();
					}

					if (dogs[i].get_breed() == breed && dogs[i].get_age() < age) {
						exists = 1;

						cout << "Breed: " << dogs[i].get_breed() << ", Name: " << dogs[i].get_name()
							<< ", Age: " << dogs[i].get_age() << ", Photo link: " << dogs[i].get_photo() << endl;


						cout << "Do you want to adopt this dog? (y/n): ";

						string answer, answer_next;
						getline(cin, answer);

						if (answer == "y") {
							adopted_dogs.add(dogs[i]);

							cout << "You adopted " << dogs[i].get_name() << ", breed " << dogs[i].get_breed() << " successfully!" << endl;

							breed = dogs[i].get_breed();
							name = dogs[i].get_name();
							dogs.remove(i);
							this->service.remove(breed, name);
							i--;

							cout << "Do you want to show the next dog? (y/n): ";
							getline(cin, answer_next);

							if (answer_next == "y") {
								i++;

								if (dogs.get_size() == 0) {
									cout << "There are no more dogs in the shelter that match the given criteria!" << endl;
									break;
								}

								if (i == dogs.get_size()) {
									i = 0;
								}

								continue;
							}
							else if (answer_next == "n") {
								break;
							} else {
								cout << "Invalid answer, please type y/n!" << endl;
							}
						}
						else if (answer == "n") {
							cout << "You chose not to adopt " << dogs[i].get_name() << ", breed " << dogs[i].get_breed() << "." << endl;

							cout << "Do you want to show the next dog? (y/n): ";
							getline(cin, answer_next);

							if (answer_next == "y") {
								i++;

								if (dogs.get_size() == 0) {
									cout << "There are no more dogs in the shelter that match the given criteria!" << endl;
									break;
								}

								if (i == dogs.get_size()) {
									cout << "i = 0" << endl;
									i = 0;
								}

								continue;
							}
							else if (answer_next == "n") {
								break;
							}
							else {
								cout << "Invalid answer, please type y/n!" << endl;
							}
						}
						else {
							cout << "Invalid answer, please type y/n!" << endl;
						}
					}
					else {
						i++;
					}
				}

				if (exists == 0) {
					cout << "There are no dogs in the shelter that match the given criteria!" << endl;
				}
				else {
					cout << "There are no more dogs in the shelter that match the given criteria!" << endl;

				}
			}

			else if (option == 3) {
				cout << "This is your adoption list: " << endl;
				for (int i = 0; i < adopted_dogs.get_size(); i++) {
					cout << i + 1 << " - Breed: " << adopted_dogs[i].get_breed() << ", Name: " << adopted_dogs[i].get_name()
						<< ", Age: " << adopted_dogs[i].get_age() << ", Photo link: " << adopted_dogs[i].get_photo() << endl;
				}
			}

			else if (option == 4) {
				cout << "You have exited the application!" << endl;
				break;
			}
			else {
				cout << "Invalid option!" << endl;
			}
		}
	}

	else if (option_start == 3) {
		cout << endl << "You have exited the application!" << endl;
	}

	else {
		cout << "Invalid option!" << endl;
	}
}