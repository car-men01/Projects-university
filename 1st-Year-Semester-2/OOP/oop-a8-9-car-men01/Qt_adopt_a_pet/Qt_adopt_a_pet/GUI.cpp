#include "GUI.h"
#include <qlabel.h>
#include <qmessagebox.h>
#include <qheaderview.h>
#include <qtabwidget.h>
#include <Windows.h>

GUI::GUI(Service& service) : service{ service }
{
	this->itDogs = this->service.get_all();
	this->currDogIndex = 0;
	
	this->buildGUI();
	this->populateList();

	connect(this->addButton, &QPushButton::clicked, this, &GUI::addButtonHandler);
	connect(this->removeButton, &QPushButton::clicked, this, &GUI::removeButtonHandler);
	connect(this->updateButton, &QPushButton::clicked, this, &GUI::updateButtonHandler);

	connect(this->nextButton, &QPushButton::clicked, this, &GUI::nextButtonHandler);
	connect(this->viewAllButton, &QPushButton::clicked, this, &GUI::viewAllButtonHandler);
	connect(this->filterButton, &QPushButton::clicked, this, &GUI::filterButtonHandler);
	connect(this->adoptButton, &QPushButton::clicked, this, &GUI::adoptButtonHandler);
	connect(this->viewAdoptButton, &QPushButton::clicked, this, &GUI::viewAdoptButtonHandler);
	connect(this->saveButton, &QPushButton::clicked, this, &GUI::saveButtonHandler);
	connect(this->openImageButton, &QPushButton::clicked, this, &GUI::openDogImage);
}

void GUI::buildAdminGUI(QTabWidget* tabWidget)
{
	QWidget* mainWidget = new QWidget{};
	QVBoxLayout* mainLayout = new QVBoxLayout{};
	this->dogsListWidget = new QTableWidget{};
	this->dogsListWidget->setColumnCount(4);
	this->dogsListWidget->setShowGrid(true);
	this->dogsListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	this->dogsListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->dogsListWidget->setHorizontalHeaderLabels(QStringList() << QString("Breed") << QString("Name") << QString("Age") << QString("Photo link"));
	this->dogsListWidget->horizontalHeader()->setStretchLastSection(true);

	mainLayout->addWidget(this->dogsListWidget);

	QGridLayout* bottomLayout = new QGridLayout{};

	this->addButton = new QPushButton{ "Add dog" };
	this->removeButton = new QPushButton{ "Remove dog" };
	this->updateButton = new QPushButton{ "Update dog" };

	bottomLayout->addWidget(this->addButton, 4, 0);
	bottomLayout->addWidget(this->removeButton, 4, 1);
	bottomLayout->addWidget(this->updateButton, 4, 2);

	mainLayout->addLayout(bottomLayout);

	mainWidget->setLayout(mainLayout);

	tabWidget->addTab(mainWidget, "Admin");
}

void GUI::buildUserGUI(QTabWidget* tabWidget)
{
	QWidget* mainWidget = new QWidget{};
	this->mainUserLayout = new QHBoxLayout{};
	QGridLayout* leftLayout = new QGridLayout{};

	this->breedInfo = new QLabel{ "Breed: " };
	this->nameInfo = new QLabel{ "Name: " };
	this->ageInfo = new QLabel{ "Age: " };
	this->imageLabel = new QLabel{ "Photo Link: " };

	leftLayout->addWidget(this->breedInfo, 0, 0);
	leftLayout->addWidget(this->nameInfo, 1, 0);
	leftLayout->addWidget(this->ageInfo, 2, 0);
	leftLayout->addWidget(this->imageLabel, 3, 0);

	this->adoptButton = new QPushButton{ "Adopt dog" };
	this->filterButton = new QPushButton{ "Filter by breed and age" };
	this->nextButton = new QPushButton{ "Next dog" };
	this->viewAllButton = new QPushButton{ "View All" };
	this->viewAdoptButton = new QPushButton{ "View Adoption List" };
	this->saveButton = new QPushButton{ "Save to file" };
	this->openImageButton = new QPushButton{ "Open dog image" };

	leftLayout->addWidget(openImageButton, 4, 0);
	leftLayout->addWidget(nextButton, 5, 0);
	leftLayout->addWidget(adoptButton, 6, 0);
	leftLayout->addWidget(viewAdoptButton, 7, 0);
	leftLayout->addWidget(viewAllButton, 8, 0);
	leftLayout->addWidget(filterButton, 9, 0);
	leftLayout->addWidget(saveButton, 10, 0);

	this->updateLabel();

	this->mainUserLayout->addLayout(leftLayout);

	mainWidget->setLayout(this->mainUserLayout);

	tabWidget->addTab(mainWidget, "User");
}

void GUI::buildChartGUI(QTabWidget* mainWidget)
{
	this->plot = new QCustomPlot{};
	this->updatePlot();

	mainWidget->addTab(this->plot, "Chart");
}

void GUI::buildGUI()
{
	this->tabWidget = new QTabWidget{ this };
	this->tabWidget->setFixedSize(800, 600);

	this->buildAdminGUI(tabWidget);
	this->buildUserGUI(tabWidget);
	this->buildChartGUI(tabWidget);

	QObject::connect(tabWidget, &QTabWidget::currentChanged, this, &GUI::tabChanged);
}

void GUI::populateList()
{
	this->dogsListWidget->setRowCount(0);

	int i = 0;
	for (auto p : this->service.get_all())
	{
		this->dogsListWidget->insertRow(i);

		this->dogsListWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(p.get_breed())));
		this->dogsListWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p.get_name())));
		this->dogsListWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(p.get_age()))));
		this->dogsListWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(p.get_photo())));
		i++;
	}

	this->dogsListWidget->resizeColumnsToContents();
}

void GUI::addButtonHandler()
{
	this->addDialog = new QWidget{};
	addDialog->setFixedSize(300, 300);
	addDialog->setWindowTitle("Add dog");

	this->breedLineEdit = new QLineEdit{};
	this->nameLineEdit = new QLineEdit{};
	this->ageLineEdit = new QLineEdit{};
	this->photoLineEdit = new QLineEdit{};

	QLabel* breedLabel = new QLabel{ "Breed" };
	QLabel* nameLabel = new QLabel{ "Name" };
	QLabel* ageLabel = new QLabel{ "Age" };
	QLabel* photoLabel = new QLabel{ "Photo link" };

	QVBoxLayout* layout = new QVBoxLayout{};

	layout->addWidget(breedLabel);
	layout->addWidget(breedLineEdit);
	layout->addWidget(nameLabel);
	layout->addWidget(nameLineEdit);
	layout->addWidget(ageLabel);
	layout->addWidget(ageLineEdit);
	layout->addWidget(photoLabel);
	layout->addWidget(photoLineEdit);

	QPushButton* confirmButton = new QPushButton{ "Confirm" };

	layout->addWidget(confirmButton);

	addDialog->setLayout(layout);
	addDialog->show();

	QObject::connect(confirmButton, &QPushButton::clicked, this, &GUI::addConfirmButtonHandler);
}

void GUI::addConfirmButtonHandler()
{
	try {
		this->service.add(this->breedLineEdit->text().toStdString(),
			this->nameLineEdit->text().toStdString(),
			std::stoi(this->ageLineEdit->text().toStdString()),
			this->photoLineEdit->text().toStdString());
		this->populateList();
	}
	catch (const std::exception& e) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
		messageBox.setFixedSize(500, 200);
		messageBox.show();
		this->addDialog->close();
	}
	this->addDialog->close();
}

void GUI::removeButtonHandler()
{
	this->removeDialog = new QWidget{};
	removeDialog->setFixedSize(300, 300);
	removeDialog->setWindowTitle("Remove dog");

	this->breedLineEdit = new QLineEdit{};
	this->nameLineEdit = new QLineEdit{};

	QLabel* breedLabel = new QLabel{ "Breed" };
	QLabel* nameLabel = new QLabel{ "Name" };

	QVBoxLayout* layout = new QVBoxLayout{};

	layout->addWidget(breedLabel);
	layout->addWidget(breedLineEdit);
	layout->addWidget(nameLabel);
	layout->addWidget(nameLineEdit);

	QPushButton* confirmButton = new QPushButton{ "Confirm" };

	layout->addWidget(confirmButton);

	removeDialog->setLayout(layout);
	removeDialog->show();

	QObject::connect(confirmButton, &QPushButton::clicked, this, &GUI::removeConfirmButtonHandler);
}

void GUI::removeConfirmButtonHandler()
{
	try {
		this->service.remove(this->breedLineEdit->text().toStdString(),
			this->nameLineEdit->text().toStdString());
		this->populateList();
	}
	catch (const std::exception& e) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
		messageBox.setFixedSize(500, 200);
		messageBox.show();
		this->removeDialog->close();
	}
	this->removeDialog->close();
}

void GUI::updateButtonHandler()
{
	this->updateDialog = new QWidget{};
	updateDialog->setFixedSize(300, 300);
	updateDialog->setWindowTitle("Update dog");

	this->breedLineEdit = new QLineEdit{};
	this->nameLineEdit = new QLineEdit{};
	this->ageLineEdit = new QLineEdit{};
	this->photoLineEdit = new QLineEdit{};

	QLabel* breedLabel = new QLabel{ "Breed" };
	QLabel* nameLabel = new QLabel{ "Name" };
	QLabel* ageLabel = new QLabel{ "New age" };
	QLabel* photoLabel = new QLabel{ "New photo link" };

	QVBoxLayout* layout = new QVBoxLayout{};

	layout->addWidget(breedLabel);
	layout->addWidget(breedLineEdit);
	layout->addWidget(nameLabel);
	layout->addWidget(nameLineEdit);
	layout->addWidget(ageLabel);
	layout->addWidget(ageLineEdit);
	layout->addWidget(photoLabel);
	layout->addWidget(photoLineEdit);

	QPushButton* confirmButton = new QPushButton{ "Confirm" };

	layout->addWidget(confirmButton);

	updateDialog->setLayout(layout);
	updateDialog->show();

	QObject::connect(confirmButton, &QPushButton::clicked, this, &GUI::updateConfirmButtonHandler);
}

void GUI::updateConfirmButtonHandler()
{
	try {
		this->service.update(this->breedLineEdit->text().toStdString(),
			this->nameLineEdit->text().toStdString(),
			std::stoi(this->ageLineEdit->text().toStdString()),
			this->photoLineEdit->text().toStdString());
		this->populateList();
	}
	catch (const std::exception& e) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error", e.what());
		messageBox.setFixedSize(500, 200);
		messageBox.show();
		this->updateDialog->close();
	}
	this->updateDialog->close();
}

void GUI::nextButtonHandler()
{
	this->currDogIndex++;
	if (this->currDogIndex == this->itDogs.size())
		this->currDogIndex = 0;
	this->updateLabel();
}

void GUI::viewAllButtonHandler()
{
	this->itDogs = this->service.get_all();
	this->currDogIndex = 0;
	this->updateLabel();
}

void GUI::filterButtonHandler()
{
	this->filterDialog = new QWidget{};
	filterDialog->setFixedSize(300, 300);
	filterDialog->setWindowTitle("Filter by breed and age");

	this->breedLineEdit = new QLineEdit{};
	this->ageLineEdit = new QLineEdit{};

	QLabel* breedLabel = new QLabel{ "Breed" };
	QLabel* ageLabel = new QLabel{ "Age" };

	QVBoxLayout* layout = new QVBoxLayout{};

	layout->addWidget(breedLabel);
	layout->addWidget(breedLineEdit);
	layout->addWidget(ageLabel);
	layout->addWidget(ageLineEdit);

	QPushButton* confirmButton = new QPushButton{ "Confirm" };

	layout->addWidget(confirmButton);

	filterDialog->setLayout(layout);
	filterDialog->show();

	QObject::connect(confirmButton, &QPushButton::clicked, this, &GUI::filterConfirmButtonHandler);
}

void GUI::filterConfirmButtonHandler()
{
	this->itDogs = this->service.get_by_breed_and_age(std::stoi(this->ageLineEdit->text().toStdString()), this->breedLineEdit->text().toStdString());
	this->currDogIndex = 0;
	this->updateLabel();
	this->filterDialog->close();
}

void GUI::adoptButtonHandler()
{
	this->service.add_to_adopted(this->itDogs[this->currDogIndex]);
	this->service.remove(this->itDogs[this->currDogIndex].get_breed(), this->itDogs[this->currDogIndex].get_name());
}

void GUI::viewAdoptButtonHandler()
{
	this->adoptDialog = new QWidget{};
	QVBoxLayout* layout = new QVBoxLayout{};
	adoptDialog->setFixedSize(500, 500);
	adoptDialog->setWindowTitle("Adoption list");

	this->adoptionListWidget = new QTableWidget{};
	this->adoptionListWidget->setColumnCount(4);
	this->adoptionListWidget->setShowGrid(true);
	this->adoptionListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	this->adoptionListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->adoptionListWidget->setHorizontalHeaderLabels(QStringList() << QString("Breed") << QString("Name") << QString("Age") << QString("Photo Link"));
	this->adoptionListWidget->horizontalHeader()->setStretchLastSection(true);

	int i = 0;
	std::vector<Dog> adoptionList = this->service.get_all_adopted()->getDogs();
	for (auto p : adoptionList)
	{
		this->adoptionListWidget->insertRow(i);

		this->adoptionListWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(p.get_breed())));
		this->adoptionListWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(p.get_name())));
		this->adoptionListWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(std::to_string(p.get_age()))));
		this->adoptionListWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(p.get_photo())));
		i++;
	}

	this->adoptionListWidget->resizeColumnsToContents();
	layout->addWidget(this->adoptionListWidget);
	this->adoptDialog->setLayout(layout);
	this->adoptDialog->show();
}

void GUI::updateLabel()
{

	if (this->currDogIndex == this->itDogs.size())
		this->currDogIndex = 0;

	if (this->itDogs.size() == 0)
	{
		this->breedInfo->setText(QString::fromStdString("Breed: "));
		this->nameInfo->setText(QString::fromStdString("Name: "));
		this->ageInfo->setText(QString::fromStdString("Age: "));
		//
		this->imageLabel->setText(QString::fromStdString("Photo Link: "));
		return;
	}

	Dog d = this->itDogs[this->currDogIndex];

	this->breedInfo->setText(QString::fromStdString("Breed: " + d.get_breed()));
	this->nameInfo->setText(QString::fromStdString("Name: " + d.get_name()));
	this->ageInfo->setText(QString::fromStdString("Age: " + std::to_string(d.get_age())));
	//
	this->imageLabel->setText(QString::fromStdString("Photo Link: " + d.get_photo()));
}

void GUI::tabChanged()
{
	if (this->tabWidget->currentIndex() == 1) {
		qDebug() << "User tab";
		this->itDogs = this->service.get_all();
		this->currDogIndex = 0;
		this->updateLabel();
	}
	else if (this->tabWidget->currentIndex() == 2) {
		qDebug() << "Chart tab";
		this->updatePlot();
	}
}

void GUI::updateAdoptionList(FileAdoptionList* newadl)
{
	this->service.updateAdoptionList(newadl);
	this->itDogs = this->service.get_all();
	this->currDogIndex = 0;
	this->updateLabel();
}

void GUI::saveButtonHandler()
{
	this->service.save_adoption_list();
	this->service.open_adoption_list();
}

void GUI::openDogImage()
{
	Dog d = this->itDogs[this->currDogIndex];
	std::string photo = d.get_photo();
	//ShellExecuteA(NULL, "open", photo.c_str(), NULL, NULL, SW_SHOWNORMAL);
	system(("start " + photo).c_str());
}

void GUI::createAdoptionList(const std::string& type)
{
	if (type == "CSV" || type == "csv")
	{
		FileAdoptionList* p = new CSVAdoptionList{ "adoption_list.csv" };
		this->updateAdoptionList(p);
	}
	else if (type == "HTML" || type == "html")
	{
		FileAdoptionList* p = new HTMLAdoptionList{ "adoption_list.html" };
		this->updateAdoptionList(p);
	}
}

void GUI::updatePlot()
{
	std::map<std::string, int> dogs_by_breed = this->service.get_by_breed();

	QVector<double> ticks;
	QVector<QString> labels;
	QVector<double> data;

	int i = 0;
	for (const auto& d : dogs_by_breed)
	{
		ticks << i + 1;
		labels << QString::fromStdString(d.first);
		data << d.second;
		i++;
	}

	this->plot->clearPlottables(); // clear existing bars
	this->plot->legend->clearItems(); // clear existing legend items

	QVector<QColor> colors = { QColor(246, 114, 128), QColor(192, 108, 132), QColor(98, 141, 189),
									QColor(250, 128, 114), QColor(133, 204, 111), QColor(108, 91, 123),
									QColor(53, 92, 125), QColor(248, 177, 149) }; 	
	int colorIndex = 0;

	for (int j = 0; j < ticks.size(); j++)
	{
		QCPBars* bar = new QCPBars(this->plot->xAxis, this->plot->yAxis);
		QColor color = colors[colorIndex % colors.size()];
		bar->setBrush(QBrush(color));
		bar->setPen(QPen(color));

		QVector<double> singleTick;
		QVector<double> singleData;
		singleTick << ticks[j];
		singleData << data[j];
		bar->setData(singleTick, singleData);
		bar->setWidth(0.5);
		bar->setName(labels[j]);
		//this->plot->addPlottable(bar);

		colorIndex++;
	}

	this->plot->legend->setVisible(true);
	this->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop | Qt::AlignRight);

	// x-axis

	//QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
	//textTicker->addTicks(ticks, labels);
	//this->plot->xAxis->setTicker(textTicker);
	//QSharedPointer<QCPAxisTicker> numberTicker(new QCPAxisTicker);

	QSharedPointer<QCPAxisTickerFixed> numberTicker(new QCPAxisTickerFixed);
	numberTicker->setTickStep(1);
	numberTicker->setScaleStrategy(QCPAxisTickerFixed::ssNone);
	this->plot->xAxis->setTicker(numberTicker);
	this->plot->xAxis->setRange(0, i + 1);
	this->plot->xAxis->setTickLabelRotation(0);
	this->plot->xAxis->setSubTicks(true);
	this->plot->xAxis->setTickLength(0, 2);
	this->plot->xAxis->setBasePen(QPen(Qt::black));
	this->plot->xAxis->setTickPen(QPen(Qt::black));
	this->plot->xAxis->grid()->setVisible(true);
	this->plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
	this->plot->xAxis->setTickLabelColor(Qt::black);
	this->plot->xAxis->setLabelColor(Qt::black);

	// y-axis
	int maxCount = *std::max_element(data.constBegin(), data.constEnd());
	this->plot->yAxis->setRange(0, maxCount + 1);
	this->plot->yAxis->setPadding(5);
	this->plot->yAxis->setLabel("Number of dogs");
	this->plot->yAxis->setBasePen(QPen(Qt::black));
	this->plot->yAxis->setTickPen(QPen(Qt::black));
	this->plot->yAxis->setSubTickPen(QPen(Qt::white));
	this->plot->yAxis->grid()->setSubGridVisible(true);
	this->plot->yAxis->setTickLabelColor(Qt::black);
	this->plot->yAxis->setLabelColor(Qt::black);
	this->plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
	this->plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

	this->plot->replot();
}
