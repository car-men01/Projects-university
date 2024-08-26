/********************************************************************************
** Form generated from reading UI file 'Qt_adopt_a_pet.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_ADOPT_A_PET_H
#define UI_QT_ADOPT_A_PET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt_adopt_a_petClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qt_adopt_a_petClass)
    {
        if (Qt_adopt_a_petClass->objectName().isEmpty())
            Qt_adopt_a_petClass->setObjectName("Qt_adopt_a_petClass");
        Qt_adopt_a_petClass->resize(600, 400);
        menuBar = new QMenuBar(Qt_adopt_a_petClass);
        menuBar->setObjectName("menuBar");
        Qt_adopt_a_petClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qt_adopt_a_petClass);
        mainToolBar->setObjectName("mainToolBar");
        Qt_adopt_a_petClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Qt_adopt_a_petClass);
        centralWidget->setObjectName("centralWidget");
        Qt_adopt_a_petClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Qt_adopt_a_petClass);
        statusBar->setObjectName("statusBar");
        Qt_adopt_a_petClass->setStatusBar(statusBar);

        retranslateUi(Qt_adopt_a_petClass);

        QMetaObject::connectSlotsByName(Qt_adopt_a_petClass);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_adopt_a_petClass)
    {
        Qt_adopt_a_petClass->setWindowTitle(QCoreApplication::translate("Qt_adopt_a_petClass", "Qt_adopt_a_pet", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Qt_adopt_a_petClass: public Ui_Qt_adopt_a_petClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_ADOPT_A_PET_H
