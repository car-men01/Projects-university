#pragma once
#include "Person.h"
#include "Event.h"
#include "Observer.h"

class Repository : public Subject
{
private:
	vector<Person> people;
	vector<Event> events;
	string peopleFile, eventsFile;
public:
	Repository(string poepleFile, string eventsFile);
	~Repository();

	void addPersonRepo(Person p);
	void addEventRepo(Event e);

	void updatePersonRepo(Person person);

	vector<Person> getPeopleRepo();
	vector<Event> getEventsRepo();

	void readPeople();
	void readEvents();
	void writePeople();
	void writeEvents();
};

