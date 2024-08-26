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

	/*Repository repo = Repository();
	Service service = Service(repo);
	UI ui = UI(service);*/

	/*Tests tests;
	tests.test_all();*/

	//ui.run();

	return 0;
}
