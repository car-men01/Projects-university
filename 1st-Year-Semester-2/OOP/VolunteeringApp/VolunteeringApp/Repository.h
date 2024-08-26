#pragma once
#include "Volunteer.h"
#include "Department.h"
#include "Observer.h"

class Repository : public Subject
{
private:
	vector<Volunteer> volunteers;
	vector<Department> departments;
	string fileVolunteers, fileDepartments;
public:
	Repository(string fileVolunteers, string fileDepartments);
	~Repository();

	void addRepoVolunteer(Volunteer v);
	void addRepoDepartment(Department d);
	void updateRepoVolunteer(Volunteer v);

	vector<Volunteer> getVolunteers();
	vector<Department> getDepartments();


	void readVolunteers();
	void readDepartments();
	void writeToVolunteers();
};

