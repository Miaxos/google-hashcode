#include "Simulation.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

void Simulation::parseData(const char *file) {
	ifstream dataFile;
	dataFile.open(file);
	string line;
	unsigned int lineCounter=1;
	getline(dataFile, line);
	Simulation::nombreTour = stoi(line);
	cout << "Nous sommes à la ligne n° " << lineCounter << "\n";
	cout << "Voici le nombre de tours de simulation: " << Simulation::nombreTour << "\n";
	lineCounter++;
	cout << "Nous sommes à la ligne n° " << lineCounter << "\n";
	getline(dataFile, line);
	const unsigned int satelliteNumber = stoi(line);
	cout << "Voici le nombre de satellites: " << satelliteNumber << "\n";
	lineCounter++;
	for (unsigned int i = lineCounter; i < lineCounter + satelliteNumber; i++) {
		cout << "Nous sommes à la ligne n° " << i << "\n";
		getline(dataFile, line);
		istringstream splitStream (line);
		string splitString;
		vector<string> contenuLigne;
		while (getline(splitStream, splitString , ' ')) {
			contenuLigne.push_back(splitString);
		}
		int latitudeSat = stoi(contenuLigne.at(0));
		int longitudeSat = stoi(contenuLigne.at(1));
		int vitLatSat = stoi(contenuLigne.at(2));
		int orientMaxTourSat = stoi(contenuLigne.at(3));
		int orientMaxTotalSat = stoi(contenuLigne.at(4));
		Satellite s(latitudeSat, longitudeSat, vitLatSat, orientMaxTourSat, orientMaxTotalSat);
		Simulation::satelliteListe.push_back(s);
	}
	lineCounter += satelliteNumber;
	cout << "Nous sommes à la ligne n° " << lineCounter << "\n";
}

