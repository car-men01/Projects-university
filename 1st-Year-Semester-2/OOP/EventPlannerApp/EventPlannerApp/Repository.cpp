#include "Repository.h"

Repository::Repository(string peopleFile, string eventsFile) : peopleFile{ peopleFile }, eventsFile{ eventsFile } {
	this->readPeople();
	this->readEvents();
}

Repository::~Repository() {
	//this->writePeople();
	//this->writeEvents();
}

void Repository::addPersonRepo(Person p) {
	this->people.push_back(p);
}

void Repository::addEventRepo(Event e) {
	this->events.push_back(e);
	this->notify();
}

void Repository::updatePersonRepo(Person person) {
	for (Person p : this->people) {
		if (p.getName() == person.getName()) {
			p = person;
			break;
		}
	}
	//this->notify();
}

vector<Person> Repository::getPeopleRepo() {
	return this->people;
}

vector<Event> Repository::getEventsRepo() {
	return this->events;
}

void Repository::readPeople() {
	ifstream file(this->peopleFile);

	if (!file.is_open())
		return;

	while (!file.eof()) {
		Person p;
		file >> p;
		this->addPersonRepo(p);
	}

	file.close();
}

void Repository::readEvents() {
	ifstream file(this->eventsFile);

	if (!file.is_open())
		return;

	while (!file.eof()) {
		Event e;
		file >> e;
		this->addEventRepo(e);
	}

	file.close();
}

void Repository::writePeople() {
	ofstream file(this->peopleFile);

	if (!file.is_open())
		return;

	for (Person p : this->people)
		file << p;

	file.close();
}

void Repository::writeEvents() {
	ofstream file(this->eventsFile);

	if (!file.is_open())
		return;

	for (Event e : this->events)
		file << e;

	file.close();
}