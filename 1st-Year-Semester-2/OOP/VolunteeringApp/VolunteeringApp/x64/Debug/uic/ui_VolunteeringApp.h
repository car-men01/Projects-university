/********************************************************************************
** Form generated from reading UI file 'VolunteeringApp.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOLUNTEERINGAPP_H
#define UI_VOLUNTEERINGAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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

class Ui_VolunteeringAppClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *descriptionlineEdit;
    QListWidget *volunteerslistWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QPushButton *suitabilitypushButton;
    QPushButton *assignpushButton;
    QListWidget *unassignedlistWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *namelineEdit;
    QLabel *label_3;
    QLineEdit *emaillineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QLineEdit *interestslineEdit;
    QPushButton *addVolunteerpushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VolunteeringAppClass)
    {
        if (VolunteeringAppClass->objectName().isEmpty())
            VolunteeringAppClass->setObjectName("VolunteeringAppClass");
        VolunteeringAppClass->resize(448, 400);
        centralWidget = new QWidget(VolunteeringAppClass);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        descriptionlineEdit = new QLineEdit(centralWidget);
        descriptionlineEdit->setObjectName("descriptionlineEdit");

        verticalLayout->addWidget(descriptionlineEdit);

        volunteerslistWidget = new QListWidget(centralWidget);
        volunteerslistWidget->setObjectName("volunteerslistWidget");

        verticalLayout->addWidget(volunteerslistWidget);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(centralWidget);
        label->setObjectName("label");

        horizontalLayout_3->addWidget(label);

        suitabilitypushButton = new QPushButton(centralWidget);
        suitabilitypushButton->setObjectName("suitabilitypushButton");

        horizontalLayout_3->addWidget(suitabilitypushButton);

        assignpushButton = new QPushButton(centralWidget);
        assignpushButton->setObjectName("assignpushButton");

        horizontalLayout_3->addWidget(assignpushButton);


        verticalLayout->addLayout(horizontalLayout_3);

        unassignedlistWidget = new QListWidget(centralWidget);
        unassignedlistWidget->setObjectName("unassignedlistWidget");

        verticalLayout->addWidget(unassignedlistWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        namelineEdit = new QLineEdit(centralWidget);
        namelineEdit->setObjectName("namelineEdit");

        horizontalLayout->addWidget(namelineEdit);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        emaillineEdit = new QLineEdit(centralWidget);
        emaillineEdit->setObjectName("emaillineEdit");

        horizontalLayout->addWidget(emaillineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");

        horizontalLayout_2->addWidget(label_4);

        interestslineEdit = new QLineEdit(centralWidget);
        interestslineEdit->setObjectName("interestslineEdit");

        horizontalLayout_2->addWidget(interestslineEdit);

        addVolunteerpushButton = new QPushButton(centralWidget);
        addVolunteerpushButton->setObjectName("addVolunteerpushButton");

        horizontalLayout_2->addWidget(addVolunteerpushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        VolunteeringAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VolunteeringAppClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 448, 21));
        VolunteeringAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VolunteeringAppClass);
        mainToolBar->setObjectName("mainToolBar");
        VolunteeringAppClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VolunteeringAppClass);
        statusBar->setObjectName("statusBar");
        VolunteeringAppClass->setStatusBar(statusBar);

        retranslateUi(VolunteeringAppClass);

        QMetaObject::connectSlotsByName(VolunteeringAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *VolunteeringAppClass)
    {
        VolunteeringAppClass->setWindowTitle(QCoreApplication::translate("VolunteeringAppClass", "VolunteeringApp", nullptr));
        label->setText(QCoreApplication::translate("VolunteeringAppClass", "Unassigned volunteers", nullptr));
        suitabilitypushButton->setText(QCoreApplication::translate("VolunteeringAppClass", "Compute suitability", nullptr));
        assignpushButton->setText(QCoreApplication::translate("VolunteeringAppClass", "Assign to department", nullptr));
        label_2->setText(QCoreApplication::translate("VolunteeringAppClass", "Name:", nullptr));
        label_3->setText(QCoreApplication::translate("VolunteeringAppClass", "Email:", nullptr));
        label_4->setText(QCoreApplication::translate("VolunteeringAppClass", "List of interests", nullptr));
        addVolunteerpushButton->setText(QCoreApplication::translate("VolunteeringAppClass", "Add volunteer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VolunteeringAppClass: public Ui_VolunteeringAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOLUNTEERINGAPP_H
