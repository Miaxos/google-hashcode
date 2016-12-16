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

    // Ajout de pointeurs vers toutes les photos dans la même liste pour un traitement plus rapide
    for(Collection& c : collectionListe)
    {
        std::vector<Photo>& photos = c.getImages();
        for(Photo& p : photos)
        {
            m_photos.push_back(&p);
            p.setCollection(&c);
        }
    }

    trierPhotos();
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

void Simulation::resolutionSimple()
{
    // on traite les satellite un par un indépendamment
    for(Satellite& s : satelliteListe)
    {
        unsigned int tour = 0;

        while(tour <= nombreTour)
        {
            // on regarde où est la prochaine photo à prendre
            EtatSatellitePhoto prochain = s.prochainePhoto(m_photos, tour, nombreTour);
            unsigned int tourObjectif = prochain.tour;

            if(prochain.photo == nullptr)
            {
                break;
            }

            // on fait le déplacement nécessaire pour prendre la photo
            while(tour < tourObjectif && tour <= nombreTour)
            {
                tour++;
                s.tourSuivant(prochain.orientLat - s.getOrientLat(), prochain.orientLong - s.getOrientLong());
            }

            // on prend la photo
            if(tour <= nombreTour)
            {
                s.prendrePhoto(*prochain.photo, tour);
            }
        }
    }


    // informations pour les tests, à supprimer pour le livrable
    std::cout << "Resultats de la resolution :" << std::endl;
    unsigned int cpt(0);
    for(const Photo* p : m_photos)
    {
        if(p->isPrise())
        {
            cpt++;
            std::cout << "Photo (" << p->getLatitude() << " ; " << p->getLongitude() << ") prise au tour " << p->getTourPhoto() << " par le satellite " << p->getIdSatellitePhotographe() << std::endl;
        }
    }
    std::cout << cpt << " photos" << std::endl;

    unsigned int score = 0, scoreMax = 0;
    for(Collection& c : collectionListe)
    {
        bool complet = true;

        for(const Photo& p : c.getImages())
        {
            if(!p.isPrise())
            {
                complet = false;
                break;
            }
        }

        if(complet)
        {
            score += c.getPoints();
        }
        scoreMax += c.getPoints();
    }

    float pourcentage = ((float) score) / ((float) scoreMax) * 100.0f;
    std::cout << score << " points sur " << scoreMax << " max (" << pourcentage << "%)" << std::endl;
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
                dataFile << p->getLatitude() << " " << p->getLongitude() << " " << p->getTourPhoto() << " " << p->getIdSatellitePhotographe() << std::endl;
            }
        }
    }
    else
    {
        cerr << "ERREUR: Fichier non disponible et/ou existant." << endl;
        exit(EXIT_FAILURE);
    }
}


void Simulation::resolutionDeux() {
    
    nombrePhotosPrises = 0;
    
    // Pour chaque sat, on regarde les pts accessibles
    /*
     * S1:  t1  |   t2  |   t3  | ...
     *      null  1,2      2,6    ...
     */
    // On commence à regarder juste en fct de d et du temps ou on peut les prendre
    std::vector<Satellite> copySat(satelliteListe);
    
    for(Satellite& s : satelliteListe)
        // On boucle sur chaque sattelites 
    {
        
        
        unsigned int tour = 0; // On regarde sur le nombre de tour
        std::vector<std::vector<Photo*>> tabs;
        std::vector<int> idtabs;
        s.instancierTab(s.pointspossibles, m_photos, nombreTour, idtabs);
        
        // On a en fonction de d et du temps lˆ ou on peut les prendre
        
        // Il s'agit de trouver le moyen d'en prendre le plus en prenant en compte qu'on peut bouger que de w entre chaque tour l'orientation de la camera.
        
        // Pour le moment on va Žviter l'optimisation sur cette partie lˆ.
        bool nophototour = true; // Si il y a eu une photo ce tour, la varible passe ˆ false
        int orientationLat = 0;
        int orientationLong = 0;
        int nbTourUseless=0;
        
        
        
        for (int i=0; i<idtabs.size(); i++) {
            //on check si on peut faire le dŽplacement necessaire de la cameras.
            int nbtourChgt = idtabs[i]-tour+nbTourUseless;
            int je = idtabs[i]-tour;
            while (0 < je)
            {
                tour++;
                je--;
                s.tourSuivant(0, 0);
            }
            if (tour == 372)
            {
                
            }
            for(int j=0; j<s.pointspossibles[idtabs[i]].size(); j++) {
                s.pointspossibles[idtabs[i]][j]->addOccuCours();
            }
            // on trie d'abord selon la latitude, puis selon le nombre doccurence restante
//            std::sort(s.pointspossibles[idtabs[i]].begin(), s.pointspossibles[idtabs[i]].end(), [] (const Photo* a, const Photo* b)
//            {
//                return b->getOccu()-b->getOccuCours() >= a->getOccu()-a->getOccuCours();
//            });
            std::sort(s.pointspossibles[idtabs[i]].begin(), s.pointspossibles[idtabs[i]].end());
            // On classe par occurence
            for(int j=0; j<s.pointspossibles[idtabs[i]].size(); j++) {
                /*
                 * Optimisation:
                 * Pour chaque ensemble de point, il s'agit de savoir qui est le mieux a etre
                 * choisi maintenant et pourquoi ?
                 */
                
                if (!(s.pointspossibles[idtabs[i]][j]->isPrise()) && nophototour)
                {
                    if(abs(s.getLat() - s.pointspossibles[idtabs[i]][j]->getLatitude()) <= s.getOrientMaxTotal() && abs(s.getLong() - s.pointspossibles[idtabs[i]][j]->getLongitude()) <= s.getOrientMaxTotal())
                        // On verifie que la photo peut effectivement tre prise par le satellite
                    {
                        // Il faut maintenant verifier si il est possible avec le nombre de tour que nous avons de faire tourner la camera du satelitte dans la position necessaire.
                        if(
                            abs(s.getLat()+orientationLat - s.pointspossibles[idtabs[i]][j]->getLatitude()) <= nbtourChgt*s.getOrientMaxTour() &&
                           abs(s.getLong()+orientationLong - s.pointspossibles[idtabs[i]][j]->getLongitude()) <= nbtourChgt*s.getOrientMaxTour()
                            )
                        {
                            // On verifie que pour passer de o1 ˆ o2 il faut moins de nombnredetour*orientationparTour
                            orientationLat = (s.pointspossibles[idtabs[i]][j]->getLatitude()-s.getLat());
                            orientationLong = (s.pointspossibles[idtabs[i]][j]->getLongitude()-s.getLong());
                            s.prendrePhoto(*s.pointspossibles[idtabs[i]][j], tour);
                            
                            nombrePhotosPrises++;
                            nbTourUseless=0;
                            nbtourChgt=0;
                            nophototour = false;
                        }
                        
                    }
//                    s.prendrePhoto(*s.pointspossibles[idtabs[i]][j], i);
//                    nophototour = false;
                    
                }
                // On parcout le vecteur 1 fois,
                // Si y'en a qui ont pas ŽtŽ pris
            }
            if (nophototour == false) {
                nophototour = true;
                
            }
            else {
                nbTourUseless=nbtourChgt;
            }
        }
        
        
//        while(tour <= nombreTour)
//        {
//        }
//   
//
    };
    // Ensuite on refait avec w
    // On a un ensemble de tableaux pour chaque sat qui correspondent aux differents chemins possible pour atteindre les points

    // On fait une combinaison des chemins pour avoir le chemin avec les point max


}

