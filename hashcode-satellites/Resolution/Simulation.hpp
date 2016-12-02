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

	public: 
		void parseData(const char *file);

        // trie les photos selon leur latitude puis leur longitude
        void trierPhotos();

        // r�solution vraiment tr�s simple et absolument pas optimis�e
        void resolutionSimple();
};