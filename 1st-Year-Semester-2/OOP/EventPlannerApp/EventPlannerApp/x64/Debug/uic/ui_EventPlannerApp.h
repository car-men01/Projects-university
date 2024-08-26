/********************************************************************************
** Form generated from reading UI file 'EventPlannerApp.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVENTPLANNERAPP_H
#define UI_EVENTPLANNERAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EventPlannerAppClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *locationLineEdit;
    QListWidget *eventsListWidget;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *nearEventsCheckBox;
    QPushButton *addPushButton;
    QPushButton *goingPushButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *nameLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *descriptionLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *eventLocationLineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *dateLineEdit;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QLineEdit *selectedDescriptionLineEdit;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QListWidget *goingListWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EventPlannerAppClass)
    {
        if (EventPlannerAppClass->objectName().isEmpty())
            EventPlannerAppClass->setObjectName("EventPlannerAppClass");
        EventPlannerAppClass->resize(569, 460);
        centralWidget = new QWidget(EventPlannerAppClass);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout_7 = new QHBoxLayout(centralWidget);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        locationLineEdit = new QLineEdit(centralWidget);
        locationLineEdit->setObjectName("locationLineEdit");

        horizontalLayout->addWidget(locationLineEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        eventsListWidget = new QListWidget(centralWidget);
        eventsListWidget->setObjectName("eventsListWidget");

        verticalLayout_2->addWidget(eventsListWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        nearEventsCheckBox = new QCheckBox(centralWidget);
        nearEventsCheckBox->setObjectName("nearEventsCheckBox");

        horizontalLayout_2->addWidget(nearEventsCheckBox);

        addPushButton = new QPushButton(centralWidget);
        addPushButton->setObjectName("addPushButton");

        horizontalLayout_2->addWidget(addPushButton);

        goingPushButton = new QPushButton(centralWidget);
        goingPushButton->setObjectName("goingPushButton");

        horizontalLayout_2->addWidget(goingPushButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        nameLineEdit = new QLineEdit(centralWidget);
        nameLineEdit->setObjectName("nameLineEdit");

        horizontalLayout_3->addWidget(nameLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        descriptionLineEdit = new QLineEdit(centralWidget);
        descriptionLineEdit->setObjectName("descriptionLineEdit");

        horizontalLayout_4->addWidget(descriptionLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");

        horizontalLayout_5->addWidget(label_4);

        eventLocationLineEdit = new QLineEdit(centralWidget);
        eventLocationLineEdit->setObjectName("eventLocationLineEdit");

        horizontalLayout_5->addWidget(eventLocationLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName("label_5");

        horizontalLayout_6->addWidget(label_5);

        dateLineEdit = new QLineEdit(centralWidget);
        dateLineEdit->setObjectName("dateLineEdit");

        horizontalLayout_6->addWidget(dateLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName("label_6");

        verticalLayout->addWidget(label_6);

        selectedDescriptionLineEdit = new QLineEdit(centralWidget);
        selectedDescriptionLineEdit->setObjectName("selectedDescriptionLineEdit");

        verticalLayout->addWidget(selectedDescriptionLineEdit);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName("label_7");

        verticalLayout_3->addWidget(label_7);

        goingListWidget = new QListWidget(centralWidget);
        goingListWidget->setObjectName("goingListWidget");

        verticalLayout_3->addWidget(goingListWidget);


        verticalLayout_4->addLayout(verticalLayout_3);


        horizontalLayout_7->addLayout(verticalLayout_4);

        EventPlannerAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(EventPlannerAppClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 569, 21));
        EventPlannerAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EventPlannerAppClass);
        mainToolBar->setObjectName("mainToolBar");
        EventPlannerAppClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(EventPlannerAppClass);
        statusBar->setObjectName("statusBar");
        EventPlannerAppClass->setStatusBar(statusBar);

        retranslateUi(EventPlannerAppClass);

        QMetaObject::connectSlotsByName(EventPlannerAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *EventPlannerAppClass)
    {
        EventPlannerAppClass->setWindowTitle(QCoreApplication::translate("EventPlannerAppClass", "EventPlannerApp", nullptr));
        label->setText(QCoreApplication::translate("EventPlannerAppClass", "Location: ", nullptr));
        nearEventsCheckBox->setText(QCoreApplication::translate("EventPlannerAppClass", "Near Events", nullptr));
        addPushButton->setText(QCoreApplication::translate("EventPlannerAppClass", "Add event", nullptr));
        goingPushButton->setText(QCoreApplication::translate("EventPlannerAppClass", "Going", nullptr));
        label_2->setText(QCoreApplication::translate("EventPlannerAppClass", "Event name:", nullptr));
        label_3->setText(QCoreApplication::translate("EventPlannerAppClass", "Desccription:", nullptr));
        label_4->setText(QCoreApplication::translate("EventPlannerAppClass", "Location:", nullptr));
        label_5->setText(QCoreApplication::translate("EventPlannerAppClass", "Date: ", nullptr));
        label_6->setText(QCoreApplication::translate("EventPlannerAppClass", "Selected event description:", nullptr));
        label_7->setText(QCoreApplication::translate("EventPlannerAppClass", "Going events:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EventPlannerAppClass: public Ui_EventPlannerAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVENTPLANNERAPP_H
