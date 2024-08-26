#include "VolunteeringApp.h"
#include <qmessagebox.h>

VolunteeringApp::VolunteeringApp(Department department, Service& service, QWidget *parent)
    : QMainWindow(parent), service{ service }, department{ department }
{
    ui.setupUi(this);
    //this->populateVolunteersList();
	this->update();
	this->showDepartmentDescription();
	this->setWindowTitle(QString::fromStdString(this->department.getName()));
	this->connectSignalsAndSlots();
}

VolunteeringApp::~VolunteeringApp()
{}

void VolunteeringApp::update()
{
	this->populateVolunteersList();
}

void VolunteeringApp::connectSignalsAndSlots()
{
	QObject::connect(this->ui.addVolunteerpushButton, &QPushButton::clicked, this, &VolunteeringApp::addVolunteer);
	QObject::connect(this->ui.suitabilitypushButton, &QPushButton::clicked, this, &VolunteeringApp::computeSuitabilityScore);
	QObject::connect(this->ui.assignpushButton, &QPushButton::clicked, this, &VolunteeringApp::assignVolunteer);

}

void VolunteeringApp::showDepartmentDescription()
{
	this->ui.descriptionlineEdit->setText(QString::fromStdString(this->department.getDescription()));
}

void VolunteeringApp::populateUnassignedVolunteersList()
{
	this->ui.unassignedlistWidget->clear();
	vector<Volunteer> unassignedVolunteers = this->service.getVolunteersByDepartment("0");
	for (Volunteer v : unassignedVolunteers)
	{
		QString itemInList = QString::fromStdString(v.getName() + " - " + v.getEmail());
		this->ui.unassignedlistWidget->addItem(itemInList);
	}  

}

void VolunteeringApp::populateVolunteersList()
{
	this->ui.volunteerslistWidget->clear();
	vector<Volunteer> volunteers = this->service.getVolunteersByDepartment(this->department.getName());
	for (Volunteer v : volunteers)
	{
		QString itemInList = QString::fromStdString(v.getName() + " - " + v.getEmail());
		this->ui.volunteerslistWidget->addItem(itemInList);
	}

	this->populateUnassignedVolunteersList();
}

void VolunteeringApp::addVolunteer()
{
	string name = this->ui.namelineEdit->text().toStdString();
	string email = this->ui.emaillineEdit->text().toStdString();
	string interests = this->ui.interestslineEdit->text().toStdString();

	if (name == "" || email == "" )
	{
		QMessageBox::critical(this, "Error", "Please fill in a name and an email!");
		return;
	}

	vector<string> listOfInterests;
	stringstream ss(interests);
	string token;
	while (getline(ss, token, ','))
	{
		listOfInterests.push_back(token);
	}
	this->service.addVolunteer(name, email, listOfInterests, "0");
	//this->populateVolunteersList();
	this->update();
}

void VolunteeringApp::computeSuitabilityScore()
{

	this->ui.unassignedlistWidget->clear();
	for (Volunteer v : this->service.getTop3Volunteers(this->department))
	{
		QString itemInList = QString::fromStdString(v.getName() + " - " + v.getEmail());
		this->ui.unassignedlistWidget->addItem(itemInList);
	}
}

void VolunteeringApp::assignVolunteer()
{

	string volunteer = this->ui.unassignedlistWidget->currentItem()->text().toStdString();

	string name;
	string email;
	stringstream ss(volunteer);

	getline(ss, name, '-');
	getline(ss, email);

	name.erase(name.end() - 1);
	email.erase(email.begin() + 1);

	Volunteer v = this->service.getVolunteerByName(name);
	this->service.assignVolunteer(v, this->department.getName());

	//this->populateVolunteersList();
	this->update();
}