#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Person
{
private:
	string name, location;
	bool organiserStatus;
public:
	Person();
	Person(string name, string location, bool organiserStatus);
	string getName();
	string getLocation();
	bool getOrganiserStatus();

	friend istream& operator>>(istream& is, Person& p);
	friend ostream& operator<<(ostream& os, Person& p);
};

