#include "Qt_adopt_a_pet.h"
#include <QtWidgets/QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    Qt_adopt_a_pet w;
//    w.show();
//    return a.exec();
//}


// mainu meu adopt a pet

/*

#include <iostream>
#include <crtdbg.h>
#include "UI.h"
#include "Dog.h"
#include "Repository.h"
#include "Service.h"
#include "Tests.h"
#include "AdoptionList.h"
#include "FileAdoptionList.h"
#include "RepoExceptions.h"

using namespace std;

int main()
{

    try {
        Repository repo("Dogs.txt");
        FileAdoptionList* p = nullptr;
        cout << "What type of file would you like to use to store the adoption list (csv/html)?" << endl;
        cout << "File type: ";
        string fileType{};
        cin >> fileType;
        cout << endl;
        if (fileType == "csv")
            p = new CSVAdoptionList{ "adoption_list.csv" };
        else if (fileType == "html")
            p = new HTMLAdoptionList{ "adoption_list.html" };
        else
            cout << "Invalid file type!" << endl;
        Service service(repo, p);
        UI ui(service);
        ui.run();
        delete p;
    }
    catch (FileException&)
    {
        cout << "Repository file could not be opened! The application will terminate." << endl;
        return 1;
    }


    return 0;
}

*/



// main pt qt



//#include "MasterC_QT.h"
//#include <QtWidgets/QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MasterC_QT w;
//    w.show();
//    return a.exec();
//}

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <crtdbg.h>
#include "UI.h"
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

