#pragma once
#include "Bacterium.h"
#include "Biologist.h"

class Repository
{
private:
	vector<Bacterium> bacteria;
	vector<Biologist> biologists;
	string fileBacteria, fileBiologists;
public:
	Repository(string fileBacteria, string fileBiologists);
	~Repository();

	void addBacterium(Bacterium b);
	void addBiologist(Biologist b);

	vector<Bacterium> getBacteria();
	vector<Biologist> getBiologists();

	void readFromBacteria();
	void readFromBiologists();
	void writeToBacteria();	
};

