#pragma once
#include <vector>
#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qlineedit.h>
#include <QCoreApplication>
#include <QtNetwork\qnetworkaccessmanager.h>
#include <QtNetwork\qnetworkrequest.h>
#include <QtNetwork\qnetworkreply.h>
#include <qlabel.h>
#include <qimage.h>
#include <qfile.h>
#include <qcustomplot.h>
#include "Service.h"

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

	void nextButtonHandler();

	void filterButtonHandler();
	void filterConfirmButtonHandler();

	void viewAllButtonHandler();

	void adoptButtonHandler();

	void viewAdoptButtonHandler();

	void updateLabel();

	void tabChanged();

	void saveButtonHandler();
	void openDogImage();

	void updatePlot();
};