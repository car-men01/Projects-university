#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;
class Biologist
{
private:
	string name;
	vector<string> listOfBacterialSpecies;
public:
	Biologist();
	Biologist(string name, vector<string> listOfBacterialSpecies);

	string getName();
	vector<string> getListOfBacterialSpecies();

	friend istream& operator>>(istream& is, Biologist& b);
	friend ostream& operator<<(ostream& os, Biologist& b);
};

