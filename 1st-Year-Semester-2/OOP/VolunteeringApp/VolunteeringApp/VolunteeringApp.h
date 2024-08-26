#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VolunteeringApp.h"
#include "Service.h"

class VolunteeringApp : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    VolunteeringApp(Department department, Service& service, QWidget *parent = nullptr);
    ~VolunteeringApp();

private:
    Ui::VolunteeringAppClass ui;
    Service& service;
    Department department;

    void update() override;
    void populateUnassignedVolunteersList();
    void populateVolunteersList();
    void showDepartmentDescription();
    void connectSignalsAndSlots();
    void addVolunteer();
    void computeSuitabilityScore();
    void assignVolunteer();
};
