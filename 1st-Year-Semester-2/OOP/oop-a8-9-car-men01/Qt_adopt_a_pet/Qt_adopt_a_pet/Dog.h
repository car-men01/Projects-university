#pragma once
#include <string>

class Dog
{
private:
	std::string breed, name;
	int age;
	std::string photo;

public:
	Dog();

	Dog(const std::string& breed, const std::string& name, int age, const std::string& photo);

	std::string get_breed() const;
	std::string get_name() const;
	int get_age() const;
	std::string get_photo() const;

	void show_photo();

	friend std::istream& operator>>(std::istream& is, Dog& dog);
	friend std::ostream& operator<<(std::ostream& os, const Dog& dog);
};
