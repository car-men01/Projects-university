#pragma once

#include <QMainWindow>
#include "ui_DepartmentsVolunteers.h"
#include "Service.h"

class DepartmentsVolunteers : public QMainWindow
{
	Q_OBJECT

public:
	DepartmentsVolunteers(Service& service, QWidget *parent = nullptr);
	~DepartmentsVolunteers();

private:
	Ui::DepartmentsVolunteersClass ui;
	Service& service;

	void populateList();
};
