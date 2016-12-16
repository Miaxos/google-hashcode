#pragma once
#include <vector>
#include "Photo.hpp"
#include "Collection.hpp"

class Simulation {
	private: 
		std::vector<Satellite> satelliteListe;
		std::vector<Collection> collectionListe;
        std::vector<Photo*> m_photos;
		unsigned int nombreTour;
		unsigned int nombrePhotosPrises;

	public:

        // Constructeur
        Simulation();

		// Ajoute les données dans les différentes classes du programme
		void parseData(const char *file);

        // trie les photos selon leur latitude puis leur longitude
        void trierPhotos();

		//trie les collections selon leur ratio d'efficacité
		void trierCollection();

        // résolution vraiment très simple et absolument pas optimisée
        void resolutionSimple();

		// résolution utilisant un système de ratio
		void resolutionRatio();

		// écrit dans le fichier de sortie
		void writeData(const char *file);
};