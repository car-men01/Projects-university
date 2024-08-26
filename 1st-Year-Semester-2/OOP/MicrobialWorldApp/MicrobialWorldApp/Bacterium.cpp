#include "Bacterium.h"

Bacterium::Bacterium() : name { "" }, species { "" }, size { 0 }, listOfDiseases { vector<string>() }
{}

Bacterium::Bacterium(string name, string species, int size, vector<string> listOfDiseases) : name { name }, species { species }, size { size }, listOfDiseases { listOfDiseases }
{}

string Bacterium::getName()
{
	return this->name;
}

string Bacterium::getSpecies()
{
	return this->species;
}

int Bacterium::getSize()
{
	return this->size;
}

vector<string> Bacterium::getListOfDiseases()
{
	return this->listOfDiseases;
}

//istream& operator>>(istream& is, Bacterium& b)
//{
//	string line;
//	getline(is, line);
//
//	string token;
//	stringstream ss(line);
//
//	getline(ss, token, '-');
//	b.name = token;
//
//	getline(ss, token, '-');
//	b.species = token;
//
//	getline(ss, token, '-');
//	b.size = stoi(token);
//
//	getline(ss, token);
//	stringstream listss(token);
//
//	while (getline(listss, token, ','))
//	{
//		b.listOfDiseases.push_back(token);
//	}
//
//	return is;
//}

istream& operator>>(istream& is, Bacterium& v)
{

	string line;
	if (getline(is, line)) {
		stringstream ss(line);
		string token;

		getline(ss, token, '-');
		v.name = token;

		getline(ss, token, '-');
		v.species = token;

		getline(ss, token, '-');
		v.size = stoi(token);

		getline(ss, token, '-');
		stringstream diseases_ss(token);
		while (getline(diseases_ss, token, ',')) {
			v.listOfDiseases.push_back(token);
		}

	}

	return is;
}

ostream& operator<<(ostream& os, Bacterium& b)
{
	os << b.name << '-';
	os << b.species << '-';
	os << b.size << '-';
	for (auto& disease : b.listOfDiseases)
	{
		os << disease << ',';
	}
	return os;
}