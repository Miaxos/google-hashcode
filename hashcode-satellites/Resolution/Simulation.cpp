#include "Simulation.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
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

void Simulation::trierPhotos()
{
    std::sort(m_photos.begin(), m_photos.end(), [] (const Photo* a, const Photo* b)
    {
        if(a->getLatitude() == b->getLatitude())
        {
            return b->getLongitude() < a->getLongitude();
        }

        return b->getLatitude() < a->getLatitude();
    });
}

