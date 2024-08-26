#include "Volunteer.h"

Volunteer::Volunteer(string name, string email, vector<string> listOfInterests, string department) :
	name { name }, email { email }, listOfInterests { listOfInterests }, department { department } {}

string Volunteer::getName() {
	return this->name;
}

string Volunteer::getEmail() {
	return this->email;
}

vector<string> Volunteer::getListOfInterests() {
	return this->listOfInterests;
}

string Volunteer::getDepartment() {
	return this->department;
}


istream& operator>>(istream& is, Volunteer& v)
{
	string line;
	if (getline(is, line)) {
		stringstream ss(line);
		string token;

		getline(ss, token, ';'); 
		v.name = token;

		getline(ss, token, ';'); 
		v.email = token;

		getline(ss, token, ';'); 
		stringstream interests_ss(token);
		while (getline(interests_ss, token, ',')) {
			v.listOfInterests.push_back(token);
		}

		getline(ss, token, ';'); 
		v.department = token;
	}

	return is;
}

ostream& operator<<(ostream& os, const Volunteer& v)
{
	os << v.name << ";" << v.email << ";";
	for (int i = 0; i < v.listOfInterests.size(); i++) {
		os << v.listOfInterests[i];
		if (i < v.listOfInterests.size() - 1) {
			os << ",";
		}
	}
	os << ";" << v.department << "\n";
	return os;
}