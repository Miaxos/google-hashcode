#include "Simulation.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void Simulation::parseData(const char *file) {
	ifstream dataFile;
	dataFile.open(file);
	string line;
	int lineCounter=1;
	while (getline(dataFile,line)) {
		if (lineCounter == 1) {
			cout << "Voici les lignes du fichier: " << line << "\n";
			lineCounter++;
		}
	}
}

