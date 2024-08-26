#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
class Event
{
private:
	string organiser, name, description, location, date;
public:
	Event();
	Event(string organiser, string name, string description, string location, string date);
	string getOrganiser();
	string getName();
	string getDescription();
	string getLocation();
	string getDate();

	string toString();

	friend istream& operator>>(istream& is, Event& e);
	friend ostream& operator<<(ostream& os, Event& e);
};

