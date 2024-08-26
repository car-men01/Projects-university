#include "Event.h"

Event::Event() {}

Event::Event(string organiser, string name, string description, string location, string date) :
	organiser{ organiser }, name{ name }, description{ description }, location{ location }, date{ date } {}

string Event::getOrganiser() { 
	return this->organiser; 
}

string Event::getName() {
	return this->name; 
}

string Event::getDescription() {
	return this->description; 
}

string Event::getLocation() {
	return this->location; 
}

string Event::getDate() {
	return this->date; 
}

string Event::toString() {
	return this->organiser + " - " + this->name + " - " + this->location + " - " + this->date;
}

istream& operator>>(istream& is, Event& e) {
	string line;
	getline(is, line);

	vector<string> tokens;
	stringstream ss(line);

	string token;

	while (getline(ss, token, ','))
		tokens.push_back(token);

	if (tokens.size() != 5)
		return is;

	e.organiser = tokens[0];
	e.name = tokens[1];
	e.description = tokens[2];
	e.location = tokens[3];
	e.date = tokens[4];

	return is;
}

ostream& operator<<(ostream& os, Event& e) {
	os << e.organiser << "," << e.name << "," << e.description << "," << e.location << "," << e.date << "\n";
	return os;
}