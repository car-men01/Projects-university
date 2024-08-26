#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;

class Bacterium
{
	string name, species;
	int size;
	vector<string> listOfDiseases;
public:
	Bacterium();
	Bacterium(string name, string species, int size, vector<string> listOfDiseases);

	string getName();
	string getSpecies();
	int getSize();
	vector<string> getListOfDiseases();

	friend istream& operator>>(istream& is, Bacterium& b);
	friend ostream& operator<<(ostream& os, Bacterium& b);
};

