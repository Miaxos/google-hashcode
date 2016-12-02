#include "Simulation.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void Simulation::parseData(const char *file) {
	ifstream dataFile;
	dataFile.open(file);
	string line;
	unsigned int lineCounter=1;
	getline(dataFile, line);
	Simulation::nombreTour = stoi(line);
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

    // Ajout des collections
	getline(dataFile, line);
	const unsigned int collectionNumber = stoi(line);
	lineCounter++;
	for (int j = 0; j < collectionNumber; j++) {
		getline(dataFile, line);
		istringstream splitStream(line);
		string splitString;
		vector<string> contenuLigne;
		while (getline(splitStream, splitString, ' ')) {
			contenuLigne.push_back(splitString);
		}
		int nbPoints = stoi(contenuLigne.at(0));
		int nbPhotos = stoi(contenuLigne.at(1));
		int nbIntervalles = stoi(contenuLigne.at(2));
		Collection c(nbPoints, nbPhotos, nbIntervalles);
		lineCounter++;

        // Ajout des photos
		for (unsigned int i = lineCounter; i < lineCounter + nbPhotos; i++) {
			getline(dataFile, line);
			istringstream splitStream(line);
			string splitString;
			vector<string> contenuLigne;
			while (getline(splitStream, splitString, ' ')) {
				contenuLigne.push_back(splitString);
			}
			int latitudePhoto = stoi(contenuLigne.at(0));
			int longitudePhoto = stoi(contenuLigne.at(1));
			c.addImage(latitudePhoto, longitudePhoto);
		}
		lineCounter += nbPhotos;

        // Ajout des intervalles
		for (unsigned int i = lineCounter; i < lineCounter + nbIntervalles; i++) {
			getline(dataFile, line);
			istringstream splitStream(line);
			string splitString;
			vector<string> contenuLigne;
			while (getline(splitStream, splitString, ' ')) {
				contenuLigne.push_back(splitString);
			}
			int debutIntervalle = stoi(contenuLigne.at(0));
			int finIntervalle = stoi(contenuLigne.at(1));
			c.addIntervalle(debutIntervalle, finIntervalle);
		}
		lineCounter += nbIntervalles;
		Simulation::collectionListe.push_back(c);

        // Ajout de pointeurs vers toutes les photos dans la même liste pour un traitement plus rapide
        std::vector<Photo> images = c.getImages();
        for(Photo& p : images)
        {
            m_photos.push_back(&p);
        }
	}

    trierPhotos();
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

void Simulation::resolutionSimple()
{
    for(Satellite& s : satelliteListe)
    {
        unsigned int tour = 0;

        while(tour <= nombreTour)
        {
            EtatSatellitePhoto prochain = s.prochainePhoto(m_photos, nombreTour);

            if(prochain.photo == nullptr)
            {
                break;
            }

            while(tour < prochain.tour && tour <= nombreTour)
            {
                tour++;
                s.tourSuivant(prochain.orientLat - s.getOrientLat(), prochain.orientLong - s.getOrientLong());
            }

            if(tour <= nombreTour)
            {
                s.prendrePhoto(*prochain.photo, prochain.tour);
            }
        }
    }

    std::cout << "Resultats de la resolution :" << std::endl;
    for(const Photo* p : m_photos)
    {
        if(p->isPrise())
        {
            std::cout << "Photo (" << p->getLatitude() << " ; " << p->getLongitude() << ") prise au tour " << p->getTourPhoto() << " par le satellite " << p->getIdSatellitePhotographe() << std::endl;
        }
    }
}

