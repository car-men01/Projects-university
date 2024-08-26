#include "Service.h"
#include <algorithm>

Service::Service(Repository& repo) : repo{ repo } {}

Service::~Service() {}

void Service::addEvent(Event e) {
	this->repo.addEventRepo(e);
}

vector<Person> Service::getAllPeople() {
	return this->repo.getPeopleRepo();
}

vector<Event> Service::getAllEvents() {
	return this->repo.getEventsRepo();
}

vector<Event> Service::getEventsSorted() {
	vector<Event> events = this->getAllEvents();
	sort(events.begin(), events.end(), [](Event e1, Event e2) {
		return e1.getDate() < e2.getDate();
	});
	return events;
}

Event Service::getEventByName(string eventName) {
	vector<Event> events = this->getAllEvents();
	for (Event e : events) {
		if (e.getName() == eventName)
			return e;
	}
}

int Service::computeDistance(string location1, string location2) {
	// extract the latitude and longitude from the first location
	stringstream ss1{ location1 };
	string lat1, lon1;
	getline(ss1, lat1, ';');
	getline(ss1, lon1, ';');

	stringstream ss2{ location2 };
	string lat2, lon2;
	getline(ss2, lat2, ';');
	getline(ss2, lon2, ';');

	// convert the latitude and longitude to double

	double lat1d = stod(lat1);
	double lon1d = stod(lon1);
	double lat2d = stod(lat2);
	double lon2d = stod(lon2);

	// compute the euclidian distance between the two points
	int distance = sqrt((lat1d - lat2d) * (lat1d - lat2d) + (lon1d - lon2d) * (lon1d - lon2d));

	return distance;
}

vector<Event> Service::getNearEvents(Person p) {
	vector<Event> events = this->getAllEvents();
	vector<Event> nearEvents;

	for (Event e : events) {
		if (this->computeDistance(p.getLocation(), e.getLocation()) < 5)
			nearEvents.push_back(e);
	}

	return nearEvents;
}

int Service::checkForExistingEvent(Event e) {
	vector<Event> events = this->getAllEvents();
	for (Event ev : events) {
		if (ev.getName() == e.getName() && ev.getLocation() == e.getLocation())
			return 1;
	}
	return 0;
}