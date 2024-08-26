/********************************************************************************
** Form generated from reading UI file 'Qt_adopt_a_pet_a10.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_ADOPT_A_PET_A10_H
#define UI_QT_ADOPT_A_PET_A10_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt_adopt_a_pet_a10Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qt_adopt_a_pet_a10Class)
    {
        if (Qt_adopt_a_pet_a10Class->objectName().isEmpty())
            Qt_adopt_a_pet_a10Class->setObjectName("Qt_adopt_a_pet_a10Class");
        Qt_adopt_a_pet_a10Class->resize(600, 400);
        menuBar = new QMenuBar(Qt_adopt_a_pet_a10Class);
        menuBar->setObjectName("menuBar");
        Qt_adopt_a_pet_a10Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qt_adopt_a_pet_a10Class);
        mainToolBar->setObjectName("mainToolBar");
        Qt_adopt_a_pet_a10Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Qt_adopt_a_pet_a10Class);
        centralWidget->setObjectName("centralWidget");
        Qt_adopt_a_pet_a10Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Qt_adopt_a_pet_a10Class);
        statusBar->setObjectName("statusBar");
        Qt_adopt_a_pet_a10Class->setStatusBar(statusBar);

        retranslateUi(Qt_adopt_a_pet_a10Class);

        QMetaObject::connectSlotsByName(Qt_adopt_a_pet_a10Class);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_adopt_a_pet_a10Class)
    {
        Qt_adopt_a_pet_a10Class->setWindowTitle(QCoreApplication::translate("Qt_adopt_a_pet_a10Class", "Qt_adopt_a_pet_a10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Qt_adopt_a_pet_a10Class: public Ui_Qt_adopt_a_pet_a10Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_ADOPT_A_PET_A10_H
