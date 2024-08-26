#include "Repository.h"

Repository::Repository(string fileVolunteers, string fileDepartments)
{
	this->fileVolunteers = fileVolunteers;
	this->fileDepartments = fileDepartments;
	this->readDepartments();
	this->readVolunteers();
}
 
Repository::~Repository() 
{
	//this->writeToVolunteers();
}

void Repository::addRepoVolunteer(Volunteer v)
{
	this->volunteers.push_back(v);
	this->notify();
}

void Repository::addRepoDepartment(Department d)
{
	this->departments.push_back(d);
}

void Repository::updateRepoVolunteer(Volunteer v)
{
	for (auto& vol : this->volunteers)
	{
		if (vol.getName() == v.getName())
		{
			vol = v;
			break;
		}
	}
	this->notify();
}

vector<Volunteer> Repository::getVolunteers()
{
	return this->volunteers;
}

vector<Department> Repository::getDepartments()
{
	return this->departments;
}


void Repository::readVolunteers()
{
	ifstream file(this->fileVolunteers);
	if (!file.is_open())
		throw exception("File not found!");

	while (!file.eof())
	{
		Volunteer v;
		file >> v;
		this->addRepoVolunteer(v);
	}
	file.close();
}

void Repository::readDepartments()
{
	ifstream file(this->fileDepartments);

	while (!file.eof())
	{
		Department d;
		file >> d;
		this->addRepoDepartment(d);
	}
	file.close();
}

void Repository::writeToVolunteers()
{
	ofstream file(this->fileVolunteers);
	

	for (const auto& d : this->volunteers) {
		file << d;
	}

	file.close();
}
