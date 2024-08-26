/********************************************************************************
** Form generated from reading UI file 'MicrobialWorldApp.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MICROBIALWORLDAPP_H
#define UI_MICROBIALWORLDAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MicrobialWorldAppClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTableView *bacteriaTableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MicrobialWorldAppClass)
    {
        if (MicrobialWorldAppClass->objectName().isEmpty())
            MicrobialWorldAppClass->setObjectName("MicrobialWorldAppClass");
        MicrobialWorldAppClass->resize(600, 400);
        centralWidget = new QWidget(MicrobialWorldAppClass);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        bacteriaTableView = new QTableView(centralWidget);
        bacteriaTableView->setObjectName("bacteriaTableView");

        horizontalLayout->addWidget(bacteriaTableView);

        MicrobialWorldAppClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MicrobialWorldAppClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        MicrobialWorldAppClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MicrobialWorldAppClass);
        mainToolBar->setObjectName("mainToolBar");
        MicrobialWorldAppClass->addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MicrobialWorldAppClass);
        statusBar->setObjectName("statusBar");
        MicrobialWorldAppClass->setStatusBar(statusBar);

        retranslateUi(MicrobialWorldAppClass);

        QMetaObject::connectSlotsByName(MicrobialWorldAppClass);
    } // setupUi

    void retranslateUi(QMainWindow *MicrobialWorldAppClass)
    {
        MicrobialWorldAppClass->setWindowTitle(QCoreApplication::translate("MicrobialWorldAppClass", "MicrobialWorldApp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MicrobialWorldAppClass: public Ui_MicrobialWorldAppClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MICROBIALWORLDAPP_H
