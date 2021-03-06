#include "Simulation.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

Simulation::Simulation() :
    nombreTour(0),
    nombrePhotosPrises(0)
{}

void Simulation::parseData(const char *file) {
	ifstream dataFile;
	dataFile.open(file);

    if(!dataFile.is_open())
    {
        cerr << "Erreur : impossible d'ouvrir le fichier " << file << " en lecture" << endl;
        exit(EXIT_FAILURE);
    }

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
	for (unsigned int j = 0; j < collectionNumber; j++) {
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
	}

    // Ajout de pointeurs vers toutes les photos dans la m�me liste pour un traitement plus rapide
	
	for(Collection& c : collectionListe)
    {
        std::vector<Photo>& photos = c.getImages();
        for(Photo& p : photos)
        {	
            m_photos.push_back(&p);
            p.setCollection(&c);
        }
    }
	trierCollection();
}

void Simulation::trierPhotos()
{
    // on trie d'abord selon la latitude, puis selon la longitude

    std::sort(m_photos.begin(), m_photos.end(), [] (const Photo* a, const Photo* b)
    {
        if(a->getLatitude() == b->getLatitude())
        {
            return b->getLongitude() > a->getLongitude();
        }

        return b->getLatitude() > a->getLatitude();
    });
}


void Simulation::trierCollection() {
	std::sort(m_photos.begin(), m_photos.end(), [](Photo* a, Photo* b)
	{
		if (a->getCollection()->getRatio() == b->getCollection()->getRatio()) {
			if (b->getCollection()->getImages().front().getLatitude() == a->getCollection()->getImages().front().getLatitude()) {
				return a->getCollection()->getImages().front().getLongitude() > b->getCollection()->getImages().front().getLongitude();
			}
			return b->getCollection()->getImages().front().getLatitude() > a->getCollection()->getImages().front().getLatitude();
		}
		return a->getCollection()->getRatio() > b->getCollection()->getRatio();
	});
}



void Simulation::resolutionSimple()
{
	// Ajout de pointeurs vers toutes les photos dans la m�me liste pour un traitement plus rapide

	for (Collection& c : collectionListe)
	{
		std::vector<Photo>& photos = c.getImages();
		for (Photo& p : photos)
		{
			m_photos.push_back(&p);
			p.setCollection(&c);
		}
	}
	trierPhotos();

    // on traite les satellite un par un ind�pendamment
    for(Satellite& s : satelliteListe)
    {
        unsigned int tour = 0;

        while(tour <= nombreTour)
        {
            // on regarde o� est la prochaine photo � prendre
            EtatSatellitePhoto prochain = s.prochainePhoto(m_photos, tour, nombreTour);
            unsigned int tourObjectif = prochain.tour;

            if(prochain.photo == nullptr)
            {
                break;
            }
			
            // on fait le d�placement n�cessaire pour prendre la photo
            while(tour < tourObjectif && tour <= nombreTour)
            {
                tour++;
                s.tourSuivant(prochain.orientLat - s.getOrientLat(), prochain.orientLong - s.getOrientLong());
            }

            // on prend la photo
            if(tour <= nombreTour)
            {
                s.prendrePhoto(*prochain.photo, tour);
				nombrePhotosPrises++;
            }
        }
    }
}

void Simulation::resolutionRatio()
{
	// Ajout de pointeurs vers toutes les photos dans la m�me liste pour un traitement plus rapide

	for (Collection& c : collectionListe)
	{
		std::vector<Photo>& photos = c.getImages();
		for (Photo& p : photos)
		{
			m_photos.push_back(&p);
			p.setCollection(&c);
		}
	}
	trierCollection();

	// on traite les satellites un par un ind�pendamment
	for (Satellite& s : satelliteListe)
	{

		unsigned int tour = 0;

		while (tour <= nombreTour)
		{
			// On d�finit la prochaine photo � prendre
			EtatSatellitePhoto prochain = s.prochainePhotoRatio(m_photos, tour, nombreTour);
			

			if (prochain.photo == nullptr)
			{
				break;
			}

			unsigned int tourObjectif = prochain.tour;
		
			// on fait le d�placement n�cessaire pour prendre la photo
			while (tour < tourObjectif && tour <= nombreTour)
			{
				tour++;
				s.tourSuivant(prochain.orientLat - s.getOrientLat(), prochain.orientLong - s.getOrientLong());
			}
			// On prend la photo une fois arriv� au tour souhait�
			if (tour <= nombreTour)
			{
				s.prendrePhoto(*prochain.photo, tour);
				nombrePhotosPrises++;
			}
		}
	}
}
void Simulation::writeData(const char *file) {
	ofstream dataFile(file);

	if (dataFile)
	{
		dataFile << nombrePhotosPrises << std::endl;
		for (const Photo* p : m_photos)
		{
			if (p->isPrise())
			{
				dataFile << p->getLatitude() << " " << p->getLongitude() << " " << p->getTourPhoto() << " " << p->getIdSatellitePhotographe() << " " << std::endl;
			}
		}
	}
	else
	{
		cerr << "ERREUR: Fichier non disponible et/ou existant." << endl;
        exit(EXIT_FAILURE);
	}
}

