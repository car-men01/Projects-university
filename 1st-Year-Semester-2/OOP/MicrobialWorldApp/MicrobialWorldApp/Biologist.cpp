#include "Biologist.h"

Biologist::Biologist() : name { "" }, listOfBacterialSpecies { vector<string>() }
{}

Biologist::Biologist(string name, vector<string> listOfBacterialSpecies) : name { name }, listOfBacterialSpecies { listOfBacterialSpecies }
{}

string Biologist::getName()
{
	return this->name;
}

vector<string> Biologist::getListOfBacterialSpecies()
{
	return this->listOfBacterialSpecies;
}

istream& operator>>(istream& is, Biologist& b)
{
	string line;
	getline(is, line);

	string token;
	stringstream ss(line);

	getline(ss, token, '-');
	b.name = token;

	getline(ss, token);
	stringstream listss(token);

	while (getline(listss, token, ','))
	{
		b.listOfBacterialSpecies.push_back(token);
	}
	
	return is;
}

ostream& operator<<(ostream& os, Biologist& b)
{
	os << b.name << '-';
	for (auto& species : b.listOfBacterialSpecies)
	{
		os << species << ',';
	}
	return os;
}