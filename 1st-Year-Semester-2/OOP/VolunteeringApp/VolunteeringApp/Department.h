#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

class Department
{
private:
	string name, description;
public:
	Department();
	Department(string name, string description);

	string getName() const;
	string getDescription() const;

	friend istream& operator>>(istream& is, Department& d);
};

