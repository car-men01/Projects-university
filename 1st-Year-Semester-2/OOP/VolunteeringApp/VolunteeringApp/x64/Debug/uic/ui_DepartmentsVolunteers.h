/********************************************************************************
** Form generated from reading UI file 'DepartmentsVolunteers.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPARTMENTSVOLUNTEERS_H
#define UI_DEPARTMENTSVOLUNTEERS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DepartmentsVolunteersClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *departmentslistWidget;
    QMenuBar *menuBar;
    QMenu *menuDepartments;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DepartmentsVolunteersClass)
    {
        if (DepartmentsVolunteersClass->objectName().isEmpty())
            DepartmentsVolunteersClass->setObjectName("DepartmentsVolunteersClass");
        DepartmentsVolunteersClass->resize(600, 400);
        centralWidget = new QWidget(DepartmentsVolunteersClass);
        centralWidget->setObjectName("centralWidget");
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(centralWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        departmentslistWidget = new QListWidget(centralWidget);
        departmentslistWidget->setObjectName("departmentslistWidget");

        verticalLayout->addWidget(departmentslistWidget);


        verticalLayout_2->addLayout(verticalLayout);

        DepartmentsVolunteersClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DepartmentsVolunteersClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuDepartments = new QMenu(menuBar);
        menuDepartments->setObjectName("menuDepartments");
        DepartmentsVolunteersClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DepartmentsVolunteersClass);
        mainToolBar->setObjectName("mainToolBar");
        DepartmentsVolunteersClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DepartmentsVolunteersClass);
        statusBar->setObjectName("statusBar");
        DepartmentsVolunteersClass->setStatusBar(statusBar);

        menuBar->addAction(menuDepartments->menuAction());

        retranslateUi(DepartmentsVolunteersClass);

        QMetaObject::connectSlotsByName(DepartmentsVolunteersClass);
    } // setupUi

    void retranslateUi(QMainWindow *DepartmentsVolunteersClass)
    {
        DepartmentsVolunteersClass->setWindowTitle(QCoreApplication::translate("DepartmentsVolunteersClass", "DepartmentsVolunteers", nullptr));
        label->setText(QCoreApplication::translate("DepartmentsVolunteersClass", "Department - number of volunteers:", nullptr));
        menuDepartments->setTitle(QCoreApplication::translate("DepartmentsVolunteersClass", "Departments", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DepartmentsVolunteersClass: public Ui_DepartmentsVolunteersClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPARTMENTSVOLUNTEERS_H
