#include "VolunteeringApp.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include "DepartmentsVolunteers.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Repository repo("volunteers.txt", "departments.txt");
    Service service{ repo };

    vector <Department> d = service.getDepartments();
    //vector <Observer*> observers;

    int nr = d.size();
    for (int i = 0; i < nr; i++)
    {
		VolunteeringApp* w = new VolunteeringApp{ d[i], service };
        repo.addObserver(w);
		w->show();
	}

    DepartmentsVolunteers w{ service };
    w.show();

    return a.exec();
}
