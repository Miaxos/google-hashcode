#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

void Parser::parseData_in(const char * file)
{
	ifstream dataFile;
	dataFile.open(file);

	if (!dataFile.is_open())
	{
		cerr << "Erreur : impossible d'ouvrir le fichier " << file << " en lecture" << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	unsigned int lineCounter = 1;
	getline(dataFile, line);
	Parser::nombreTour = stoi(line);
	lineCounter++;
	getline(dataFile, line);

	// Ajout des satellites
	const unsigned int satelliteNumber = stoi(line);
	lineCounter++;
	for (unsigned int i = lineCounter; i < lineCounter + satelliteNumber; i++) {
		getline(dataFile, line);
		istringstream splitStream(line);
		string splitString;
		vector<string> contenuLigne;
		while (getline(splitStream, splitString, ' ')) {
			contenuLigne.push_back(splitString);
		}
		int latitudeSat = stoi(contenuLigne.at(0));
		int longitudeSat = stoi(contenuLigne.at(1));
		int vitLatSat = stoi(contenuLigne.at(2));
		int orientMaxTourSat = stoi(contenuLigne.at(3));
		int orientMaxTotalSat = stoi(contenuLigne.at(4));
		Satellite s(latitudeSat, longitudeSat, vitLatSat, orientMaxTourSat, orientMaxTotalSat);
		Parser::list_satellite_in.push_back(s);
	}
	lineCounter += satelliteNumber;
}
