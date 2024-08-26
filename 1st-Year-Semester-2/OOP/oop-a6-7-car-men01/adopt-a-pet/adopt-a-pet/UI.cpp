#include "UI.h"
#include <iostream>
#include <crtdbg.h>
#include <string>

using namespace std;


UI::UI(const Service& service) : service{ service } {}

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

void UI::save_adoption_list_to_file()
{
	std::string filename;
	cout << "Input the file name (absolute path): ";
	getline(cin, filename);

	try
	{
		this->service.save_adoption_list();

		if (this->service.get_all_adopted() == nullptr)
		{
			cout << "The adoption list cannot be displayed!" << endl;
			return;
		}
	}
	catch (FileException& e)
	{
		cout << e.what() << endl;
	}
}

void UI::display_all()
{
	int i = 1;
	for (const Dog& dog : this->service.get_all())
	{
		cout << i << " - Breed: " << dog.get_breed() << ", Name: " << dog.get_name()
			<< ", Age: " << dog.get_age() << ", Photo link: " << dog.get_photo() << endl;
		i++;
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
	cout << "2. Display all the dogs of a given breed having the age less than a given number" << endl;
	cout << "3. Display the adoption list" << endl;
	cout << "4. See the file adoption list" << endl;
	cout << "5. Exit the application" << endl;
	cout << endl;
}


void UI::run()
{
	int option, option_start;
	string breed, name, photo;
	int age;

	//this->service.add_generated_dogs();
	std::vector<Dog> dogs = this->service.get_all();
	std::vector<Dog> adopted_dogs;

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

				while (i < dogs.size()) {
					cout << "Breed: " << dogs[i].get_breed() << ", Name: " << dogs[i].get_name()
						<< ", Age: " << dogs[i].get_age() << ", Photo link: " << dogs[i].get_photo() << endl;
					cout << "Do you want to adopt this dog? (y/n): ";

					string answer, answer_next;
					getline(cin, answer);

					if (answer == "y") {
						adopted_dogs.push_back(dogs[i]);

						/// Asta am modificat acuma
						this->service.add_to_adopted(dogs[i]);

						cout << "You adopted " << dogs[i].get_name() << ", breed " << dogs[i].get_breed() << " successfully!" << endl;


						breed = dogs[i].get_breed();
						name = dogs[i].get_name();
						dogs.erase(dogs.begin() + i);
						this->service.remove(breed, name);
						i--;

						cout << "Do you want to show the next dog? (y/n): ";
						getline(cin, answer_next);

						if (answer_next == "y") {
							i++;

							if (dogs.size() == 0) {
								cout << "There are no more dogs in the shelter!" << endl;
								break;
							}

							if (i == dogs.size()) {
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
					else if (answer == "n") {
						cout << "You chose not to adopt " << dogs[i].get_name() << ", breed " << dogs[i].get_breed() << "." << endl;

						cout << "Do you want to show the next dog? (y/n): ";
						getline(cin, answer_next);

						if (answer_next == "y") {
							i++;
							if (dogs.size() == 0)
							{
								cout << "There are no more dogs in the shelter!" << endl;
								break;
							}

							if (i == dogs.size()) {
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
				std::vector<Dog> result;

				cout << "Enter the breed: ";
				getline(cin, breed);
				cout << "Enter the age: ";
				cin >> age;
				cin.ignore();

				int ok = 0, i = 0, exists = 0;

				if (breed == "") {
					result = this->service.get_all();
				}
				else {
					result = this->service.get_by_breed_and_age(age, breed);
				}

				while (i < result.size()) {

					if (result.size() > 0) {
						exists = 1;

						cout << "Breed: " << result[i].get_breed() << ", Name: " << result[i].get_name()
							<< ", Age: " << result[i].get_age() << ", Photo link: " << result[i].get_photo() << endl;


						cout << "Do you want to adopt this dog? (y/n): ";

						string answer, answer_next;
						getline(cin, answer);

						if (answer == "y") {
							adopted_dogs.push_back(result[i]);

							/// Asta am modificat acuma
							this->service.add_to_adopted(dogs[i]);

							cout << "You adopted " << result[i].get_name() << ", breed " << result[i].get_breed() << " successfully!" << endl;

							breed = result[i].get_breed();
							name = result[i].get_name();
							result.erase(result.begin() + i);
							this->service.remove(breed, name);
							i--;

							cout << "Do you want to show the next dog? (y/n): ";
							getline(cin, answer_next);

							if (answer_next == "y") {
								i++;

								if (result.size() == 0) {
									cout << "There are no more dogs in the shelter that match the given criteria!" << endl;
									break;
								}

								if (i == result.size()) {
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
						else if (answer == "n") {
							cout << "You chose not to adopt " << result[i].get_name() << ", breed " << result[i].get_breed() << "." << endl;

							cout << "Do you want to show the next dog? (y/n): ";
							getline(cin, answer_next);

							if (answer_next == "y") {
								i++;

								if (result.size() == 0) {
									cout << "There are no more dogs in the shelter that match the given criteria!" << endl;
									break;
								}

								if (i == result.size()) {
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
			}

			else if (option == 3) {
				cout << "This is your adoption list: " << endl;
				for (int i = 0; i < adopted_dogs.size(); i++) {
					cout << i + 1 << " - Breed: " << adopted_dogs[i].get_breed() << ", Name: " << adopted_dogs[i].get_name()
						<< ", Age: " << adopted_dogs[i].get_age() << ", Photo link: " << adopted_dogs[i].get_photo() << endl;
				}
			}

			else if (option == 4) {
				this->save_adoption_list_to_file();
				this->service.open_adoption_list();
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

	else if (option_start == 3) {
		cout << endl << "You have exited the application!" << endl;
	}

	else {
		cout << "Invalid option!" << endl;
	}
}