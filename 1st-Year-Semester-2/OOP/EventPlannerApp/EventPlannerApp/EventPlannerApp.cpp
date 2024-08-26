#include "EventPlannerApp.h"
#include <QMessageBox>

EventPlannerApp::EventPlannerApp(Person p, Service& service, QWidget *parent)
    : QMainWindow(parent), service{ service }, p { p }
{
    ui.setupUi(this);
   // this->populateEventsList();
	this->setWindowTitle(QString::fromStdString(p.getName()));
	this->showPersonLocation();
	this->connectSignalsAndSlots();
	this->update();
}

EventPlannerApp::~EventPlannerApp()
{}

void EventPlannerApp::update() {
	this->populateEventsList();
}

void EventPlannerApp::connectSignalsAndSlots() {
	QObject::connect(this->ui.nearEventsCheckBox, &QCheckBox::stateChanged, this, &EventPlannerApp::populateEventsList);
	QObject::connect(this->ui.addPushButton, &QPushButton::clicked, this, &EventPlannerApp::addEvent);
	//QObject::connect(this->ui.selectedDescriptionLineEdit, &QLineEdit::textChanged, this, &EventPlannerApp::showEventDescription);
}

void EventPlannerApp::showPersonLocation() {
	string location = this->p.getLocation();
	this->ui.locationLineEdit->setText(QString::fromStdString(location));
}

void EventPlannerApp::showEventDescription() {
	string eventItem = this->ui.eventsListWidget->currentItem()->text().toStdString();
	string eventName, organiser, location, date;

	stringstream ss(eventItem);
	getline(ss, organiser, '-');
	getline(ss, eventName, '-');
	getline(ss, location, '-');
	getline(ss, date);

	Event event = this->service.getEventByName(eventName);

	this->ui.selectedDescriptionLineEdit->setText(QString::fromStdString(event.getDescription()));
}

void EventPlannerApp::populateEventsList() {
	this->ui.eventsListWidget->clear();
	vector<Event> events;

	if (this->ui.nearEventsCheckBox->isChecked())
		events= this->service.getNearEvents(this->p);
	else
		events = this->service.getEventsSorted();

	for (Event e : events) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(e.toString()));
		if (this->p.getOrganiserStatus() == true && e.getOrganiser() == this->p.getName())
			item->setBackground(Qt::green);
		this->ui.eventsListWidget->addItem(item);
	}
}

void EventPlannerApp::addEvent() {
	string name = this->ui.nameLineEdit->text().toStdString();
	string description = this->ui.descriptionLineEdit->text().toStdString();
	string location = this->ui.eventLocationLineEdit->text().toStdString();
	string date = this->ui.dateLineEdit->text().toStdString();

	Event e{ p.getName(), name, description, location, date};

	if (this->service.checkForExistingEvent(e) == 1) {
		QMessageBox::critical(this, "Error", "Event already exists!");
		return;
	}

	if (p.getOrganiserStatus() == false) {
		QMessageBox::critical(this, "Error", "You are not an organiser!");
		return;
	}
	
	this->service.addEvent(e);
	this->populateEventsList();
}

