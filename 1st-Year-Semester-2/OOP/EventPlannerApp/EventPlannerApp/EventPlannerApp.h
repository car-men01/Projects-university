#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EventPlannerApp.h"
#include "Service.h"

class EventPlannerApp : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    EventPlannerApp(Person p, Service& service, QWidget *parent = nullptr);
    ~EventPlannerApp();

private:
    Service& service;
    Person p;
    Ui::EventPlannerAppClass ui;

    void update() override;
    void populateEventsList();
    void showPersonLocation();
    void showEventDescription();
    void connectSignalsAndSlots();
    void addEvent();
};
