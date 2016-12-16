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

		// Ajoute les donn�es dans les diff�rentes classes du programme
		void parseData(const char *file);

        // trie les photos selon leur latitude puis leur longitude
        void trierPhotos();

		//trie les collections selon leur ratio d'efficacit�
		void trierCollection();

        // r�solution vraiment tr�s simple et absolument pas optimis�e
        void resolutionSimple();

		// r�solution utilisant un syst�me de ratio
		void resolutionRatio();

		// �crit dans le fichier de sortie
		void writeData(const char *file);
};