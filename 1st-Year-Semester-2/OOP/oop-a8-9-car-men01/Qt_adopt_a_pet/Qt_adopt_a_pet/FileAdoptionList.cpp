#include "FileAdoptionList.h"
#include <fstream>
#include <Windows.h>
#include <shellapi.h>

FileAdoptionList::FileAdoptionList(std::string filename) : filename{ filename } {}

CSVAdoptionList::CSVAdoptionList(std::string filename) : FileAdoptionList(filename) {}

void CSVAdoptionList::writeToFile() {
	std::ofstream out(filename);
	for (auto d : dogs) {
		out << d;
	}
	out.close();
}

void CSVAdoptionList::displayAdoptionList() {
	ShellExecuteA(NULL, "open", "excel.exe", filename.c_str(), NULL, SW_SHOWMAXIMIZED);
}

HTMLAdoptionList::HTMLAdoptionList(std::string filename) : FileAdoptionList(filename) {}

void HTMLAdoptionList::writeToFile() {
	std::ofstream out(filename);
	out << "<!DOCTYPE html>\n<html>\n<head>\n<title>Adoption List</title>\n</head>\n<body>\n<table border=\"1\">\n<tr>\n<td>Name</td>\n<td>Breed</td>\n<td>Age</td>\n<td>Photograph</td>\n</tr>\n";
	for (auto d : dogs) {
		out << "<tr>\n<td>" << d.get_name() << "</td>\n<td>" << d.get_breed() << "</td>\n<td>" << d.get_age() << "</td>\n<td><a href=\"" << d.get_photo() << "\">Link</a></td>\n</tr>\n";
	}
	out << "</table>\n</body>\n</html>";
	out.close();
}

void HTMLAdoptionList::displayAdoptionList() {
	std::string path = "file:///D:/UBB/Semestrul_II/oop/assignments/oop-a8-9-car-men01/Qt_adopt_a_pet/Qt_adopt_a_pet/adoption_list.html";
	ShellExecuteA(NULL, "open", "chrome.exe", path.c_str(), NULL, SW_SHOWMAXIMIZED);
}
