#pragma once
#include <vector>
#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <QCoreApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTableView>
#include <QApplication>
#include <QtNetwork\qnetworkaccessmanager.h>
#include <QtNetwork\qnetworkrequest.h>
#include <QtNetwork\qnetworkreply.h>
#include <qlabel.h>
#include <qimage.h>
#include <qfile.h>
#include <qcustomplot.h>
#include <QKeySequence>
#include <QShortcut>
#include "Service.h"
#include "Action.h"
#include "TableModel.h"

class GUI : public QWidget
{
private:
	Service& service;
	std::vector<Dog> itDogs;
	int currDogIndex;

	QTableWidget* dogsListWidget;
	QTableWidget* adoptionListWidget;
	QTabWidget* tabWidget;

	QLineEdit* breedLineEdit;
	QLineEdit* nameLineEdit;
	QLineEdit* ageLineEdit;
	QLineEdit* photoLineEdit;

	QPushButton* addButton;
	QPushButton* removeButton;
	QPushButton* updateButton;

	QPushButton* undoButton;
	QPushButton* redoButton;
	QShortcut* undoShortcut;
	QShortcut* redoShortcut;

	QPushButton* viewAdoptButton;
	QPushButton* adoptButton;
	QPushButton* nextButton;
	QPushButton* filterButton;
	QPushButton* viewAllButton;
	QPushButton* saveButton;
	QPushButton* openImageButton;

	QWidget* addDialog;
	QWidget* removeDialog;
	QWidget* updateDialog;

	QWidget* adoptDialog;
	QWidget* filterDialog;

	QLabel* breedInfo;
	QLabel* nameInfo;
	QLabel* ageInfo;
	QLabel* imageLabel;

	QHBoxLayout* mainUserLayout;
	QCustomPlot* plot;

public:
	GUI(Service& service);

	void createAdoptionList(const std::string& fileType);
	void updateAdoptionList(FileAdoptionList* newadl);

private:
	void buildAdminGUI(QTabWidget* mainWidget);
	void buildUserGUI(QTabWidget* mainWidget);
	void buildChartGUI(QTabWidget* mainWidget);

	void buildGUI();
	void populateList();

	void addButtonHandler();
	void addConfirmButtonHandler();

	void removeButtonHandler();
	void removeConfirmButtonHandler();

	void updateButtonHandler();
	void updateConfirmButtonHandler();

	void undoButtonHandler();
	void redoButtonHandler();

	void nextButtonHandler();

	void filterButtonHandler();
	void filterConfirmButtonHandler();

	void viewAllButtonHandler();

	void adoptButtonHandler();

	void viewAdoptButtonHandler();

	void saveButtonHandler();
	void openDogImage();

	void updateLabel();

	void tabChanged();

	void updatePlot();
};