#include "Department.h"

Department::Department() : name { " " }, description { " " } {}

Department::Department(string name, string description) : name { name }, description { description }
{}

string Department::getName() const
{
	return this->name;
}

string Department::getDescription() const
{
	return this->description;
}

istream& operator>>(istream& is, Department& d)
{
	string line;
	getline(is, line);

	vector<string> tokens;
	stringstream ss(line);
	string token;
	while (getline(ss, token, ':'))
		tokens.push_back(token);

	if (tokens.size() != 2)
		return is;

	d.name = tokens[0];
	d.description = tokens[1];

	return is;
}

