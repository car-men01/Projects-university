#include "Person.h"

Person::Person() {}

Person::Person(string name, string location, bool organiserStatus) :
	name{ name }, location{ location }, organiserStatus{ organiserStatus } {}

string Person::getName() {
	return this->name;
}

string Person::getLocation() {
	return this->location;
}

bool Person::getOrganiserStatus() {
	return this->organiserStatus;
}

istream& operator>>(istream& is, Person& p) {
	string line;
	getline(is, line);

	vector<string> tokens;
	stringstream ss(line);

	string token;

	while (getline(ss, token, ','))
		tokens.push_back(token);

	if (tokens.size() != 3)
		return is;

	p.name = tokens[0];
	p.location = tokens[1];
	p.organiserStatus = stoi(tokens[2]);

	return is;
}

ostream& operator<<(ostream& os, Person& p) {
	os << p.name << "," << p.location << "," << p.organiserStatus << "\n";
	return os;
}
