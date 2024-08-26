#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Department.h"
#include "Observer.h"
	
using namespace std;

class Volunteer
{
private:
	string name, email;
	vector<string> listOfInterests;
	string department;

public:
	Volunteer() = default;
	Volunteer(string name, string email, vector<string> listOfInterests, string department);

	string getName();
	string getEmail();
	vector<string> getListOfInterests();
	string getDepartment();

	friend istream& operator>>(istream& is, Volunteer& v);
	friend ostream& operator<<(ostream& os, const Volunteer& v);
};

