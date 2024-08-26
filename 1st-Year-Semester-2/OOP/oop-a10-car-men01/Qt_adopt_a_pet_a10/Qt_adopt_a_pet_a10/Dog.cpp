#include "Dog.h"
#include "Utils.h"
#include <iostream>
#include <Windows.h>
#include <shellapi.h>

using namespace std;

/// <summary>
/// The default constructor of the dog
/// </summary>
Dog::Dog() : breed{ "" }, name{ "" }, age{ 0 }, photo{ "" } {}

/// <summary>
/// The constructor of the dog
/// </summary>
/// <param name="breed"> Dog breed </param>
/// <param name="name"> Dog name </param>
/// <param name="age"> Dog age </param>
/// <param name="photo"> Dog photo link </param>
Dog::Dog(const std::string& breed, const std::string& name, int age, const std::string& photo)
	: breed{ breed }, name{ name }, age{ age }, photo{ photo } {}

/// <summary>
/// Gets the breed of the dog
/// </summary>
/// <returns> The breed of the dog </returns>
std::string Dog::get_breed() const
{
	return this->breed;
}

/// <summary>
/// Gets the name of the dog
/// </summary>
/// <returns> The name of the dog </returns>
std::string Dog::get_name() const
{
	return this->name;
}

/// <summary>
/// Gets the age of the dog
/// </summary>
/// <returns> The age of the dog </returns>
int Dog::get_age() const
{
	return this->age;
}

/// <summary>
/// Gets the photo link of the dog
/// </summary>
/// <returns> The photo link of the dog </returns>
std::string Dog::get_photo() const
{
	return this->photo;
}

void Dog::show_photo()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->get_photo().c_str(), NULL, SW_SHOWMAXIMIZED);
}

istream& operator>>(istream& is, Dog& dog)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 4)
		return is;

	dog.breed = tokens[0];
	dog.name = tokens[1];
	dog.age = stoi(tokens[2]);
	dog.photo = tokens[3];

	return is;

}

ostream& operator<<(ostream& os, const Dog& dog)
{
	os << dog.breed << "," << dog.name << "," << dog.age << "," << dog.photo << "\n";
	return os;
}
