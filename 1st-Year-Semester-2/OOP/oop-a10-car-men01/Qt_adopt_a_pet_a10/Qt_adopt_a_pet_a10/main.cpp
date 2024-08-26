#include "Qt_adopt_a_pet_a10.h"
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <crtdbg.h>
#include "Dog.h"
#include "Repository.h"
#include "Service.h"
#include "AdoptionList.h"
#include "FileAdoptionList.h"
#include "RepoExceptions.h"
#include "GUI.h"

using namespace std;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Repository repo("Dogs.txt");
    FileAdoptionList* p = nullptr;
    Service service(repo);
    GUI gui(service);

    // Create widgets
    QLabel label("What type of file would you like to use to store the Adoption List (CSV/HTML)?");
    QLineEdit fileTypeEdit;
    QPushButton startButton("Start");

    // Layout setup
    QVBoxLayout layout;
    layout.addWidget(&label);
    layout.addWidget(&fileTypeEdit);
    layout.addWidget(&startButton);

    // Signal-slot connections
    QObject::connect(&startButton, &QPushButton::clicked, [&]() {
        QString fileType = fileTypeEdit.text().trimmed().toLower();
        if (fileType == "csv" || fileType == "html")
        {
            // Start the application
            // For now, let's just print the file type
            try {
                std::string type = fileType.toStdString();
                gui.createAdoptionList(type);
                gui.show();
                delete p;
            }
            catch (FileException&)
            {
                cout << "Repository file could not be opened! The application will terminate." << endl;
            }
            qDebug() << "File type selected:" << fileType;
        }
        else
        {
            QMessageBox::critical(nullptr, "Error", "Invalid file type. Please enter CSV or HTML.");
        }
        });

    // Create a main window
    QWidget window;
    window.setLayout(&layout);
    window.show();

    return app.exec();
}

