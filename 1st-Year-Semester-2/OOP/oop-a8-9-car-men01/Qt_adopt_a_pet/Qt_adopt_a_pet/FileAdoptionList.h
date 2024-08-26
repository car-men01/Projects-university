#pragma once
#include "AdoptionList.h"

class FileAdoptionList : public AdoptionList {
protected:
	std::string filename;
public:
	FileAdoptionList(std::string filename);

	virtual void writeToFile() = 0;
	virtual void displayAdoptionList() = 0;
};

class CSVAdoptionList : public FileAdoptionList {
public:
	CSVAdoptionList(std::string filename);
	void writeToFile();
	void displayAdoptionList();
};

class HTMLAdoptionList : public FileAdoptionList {
public:
	HTMLAdoptionList(std::string filename);
	void writeToFile();
	void displayAdoptionList();
};
