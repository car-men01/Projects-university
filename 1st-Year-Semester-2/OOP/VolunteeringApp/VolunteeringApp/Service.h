#pragma once
#include "Repository.h"


class Service
{
private:
	Repository& repo;
public:
	Service(Repository& repo);
	~Service();

	void addVolunteer(string name, string email, vector<string> listOfInterests, string department);
	vector<Volunteer> getVolunteers();

	void addDepartment(string name, string description);
	vector<Department> getDepartments();

	vector<Volunteer> getVolunteersByDepartment(string department);

	float computeSuitabilityScore(Volunteer v, Department d);
	vector<Volunteer> getTop3Volunteers(Department d);

	void assignVolunteer(Volunteer v, string department);
	Volunteer getVolunteerByName(string name);

	vector<pair<Department, int>> showDepartmentNrVolunteers();
	
};

