#include "Repository.h"

Repository::Repository(string fileBacteria, string fileBiologists) : fileBacteria{ fileBacteria }, fileBiologists{ fileBiologists }
{
	this->readFromBacteria();
	this->readFromBiologists();
}

Repository::~Repository()
{}

void Repository::addBacterium(Bacterium b)
{
	this->bacteria.push_back(b);
	//this->writeToBacteria();
}

void Repository::addBiologist(Biologist b)
{
	this->biologists.push_back(b);
}

vector<Bacterium> Repository::getBacteria()
{
	return this->bacteria;
}

vector<Biologist> Repository::getBiologists()
{
	return this->biologists;
}

void Repository::readFromBacteria()
{
	ifstream file(this->fileBacteria);
	Bacterium b;
	while (file >> b)
	{
		this->addBacterium(b);
	}
	file.close();
}

void Repository::readFromBiologists()
{
	ifstream file(this->fileBiologists);
	Biologist b;
	while (file >> b)
	{
		this->addBiologist(b);
	}
	file.close();
}

void Repository::writeToBacteria()
{
	ofstream file(this->fileBacteria);
	for (auto& b : this->bacteria)
	{
		file << b << '\n';
	}
	file.close();
}