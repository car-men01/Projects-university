#include "DepartmentsVolunteers.h"

DepartmentsVolunteers::DepartmentsVolunteers(Service& service, QWidget *parent)
	: QMainWindow(parent), service{ service }
{
	ui.setupUi(this);

	this->populateList();
}

DepartmentsVolunteers::~DepartmentsVolunteers()
{}

void DepartmentsVolunteers::populateList()
{
	this->ui.departmentslistWidget->clear();
	vector<pair<Department, int>> departments = this->service.showDepartmentNrVolunteers();
	for (auto p : departments)
	{
		QString itemInList = QString::fromStdString(p.first.getName() + " - " + to_string(p.second) + " volunteers");
		this->ui.departmentslistWidget->addItem(itemInList);
	}
}
