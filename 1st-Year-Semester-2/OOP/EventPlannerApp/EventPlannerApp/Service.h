#pragma once
#include "Repository.h"

class Service
{
private:
	Repository& repo;
public:
	Service(Repository& repo);
	~Service();

	void addEvent(Event e);

	vector<Person> getAllPeople();
	vector<Event> getAllEvents();

	vector<Event> getEventsSorted();
	int computeDistance(string location1, string location2);
	vector<Event> getNearEvents(Person p);

	int checkForExistingEvent(Event e);
	Event getEventByName(string eventName);
};

