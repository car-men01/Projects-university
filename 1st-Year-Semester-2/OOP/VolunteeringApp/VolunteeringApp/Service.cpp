#include "Service.h"
#include <algorithm>

Service::Service(Repository& repo) : repo{ repo } {}

Service::~Service() {}

void Service::addVolunteer(string name, string email, vector<string> listOfInterests, string department)
{
	Volunteer v{ name, email, listOfInterests, department };
	this->repo.addRepoVolunteer(v);
	this->repo.writeToVolunteers();
}

vector<Volunteer> Service::getVolunteers()
{
	return this->repo.getVolunteers();
}

void Service::addDepartment(string name, string description)
{
	Department d{ name, description };
	this->repo.addRepoDepartment(d);
}

vector<Department> Service::getDepartments()
{
	return this->repo.getDepartments();
}

vector<Volunteer> Service::getVolunteersByDepartment(string department)
{
	vector<Volunteer> volunteersByDepartment;
	for (Volunteer v : this->getVolunteers()) {
		if (v.getDepartment() == department)
			volunteersByDepartment.push_back(v);
	}
	return volunteersByDepartment;
}

float Service::computeSuitabilityScore(Volunteer v, Department d)
{
	float numberOfInterests = 0;
	float score = 0;
	float numberOfWords = 1;
	for (string interest : v.getListOfInterests()) {
		if (d.getDescription().find(interest) != string::npos)
			numberOfInterests++;
	}
	for (char c : d.getDescription()) {
		if (c == ' ')
			numberOfWords++;
	}
	score = numberOfInterests / numberOfWords;
	
	return score;
}

vector<Volunteer> Service::getTop3Volunteers(Department d)
{
	vector<Volunteer> volunteers = this->getVolunteersByDepartment("0");

	vector<pair<Volunteer, float>> volunteersWithScores;
	for (Volunteer v : volunteers) {
		float score = this->computeSuitabilityScore(v, d);
		volunteersWithScores.push_back(make_pair(v, score));
	}

	sort(volunteersWithScores.begin(), volunteersWithScores.end(),
				[](pair<Volunteer, float> p1, pair<Volunteer, float> p2) {return p1.second > p2.second; });

	vector<Volunteer> top3Volunteers;
	for (int i = 0; i < 3; i++) {
		if (i == volunteersWithScores.size())
			break;
		top3Volunteers.push_back(volunteersWithScores[i].first);
	}

	return top3Volunteers;
}

void Service::assignVolunteer(Volunteer v, string department)
{
	Volunteer newVolunteer { v.getName(), v.getEmail(), v.getListOfInterests(), department };
	this->repo.updateRepoVolunteer(newVolunteer);
	this->repo.writeToVolunteers();
}

Volunteer Service::getVolunteerByName(string name)
{
	vector<Volunteer> volunteers = this->getVolunteers();
	for (Volunteer v : volunteers) {
		if (v.getName() == name)
			return v;
	}
	return Volunteer{};
}

vector<pair<Department, int>> Service::showDepartmentNrVolunteers()
{
	vector<pair<Department, int>> departmentsWithNrVolunteers;
	vector<Department> departments = this->getDepartments();

	for (Department d : departments) {
		int nrVolunteers = 0;
		for (Volunteer v : this->getVolunteers()) {
			if (v.getDepartment() == d.getName())
				nrVolunteers++;
		}
		departmentsWithNrVolunteers.push_back(make_pair(d, nrVolunteers));
	}

	sort(departmentsWithNrVolunteers.begin(), departmentsWithNrVolunteers.end(), 
		[](pair<Department, int> p1, pair<Department, int> p2) {return p1.second < p2.second; });

	return departmentsWithNrVolunteers;
}