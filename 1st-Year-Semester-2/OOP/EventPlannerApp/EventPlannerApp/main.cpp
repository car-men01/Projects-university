#include "EventPlannerApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Repository repo{ "people.txt", "events.txt" };
    Service service{ repo };

    vector<Person> people = service.getAllPeople();

    for (Person p : people) {
        EventPlannerApp *w = new EventPlannerApp{ p, service };
        repo.addObserver(w);
        w->show();
    }

   // EventPlannerApp w;
   // w.show();
    return a.exec();
}
