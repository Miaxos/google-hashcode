#pragma once
#include <vector>
#include "Photo.hpp"
#include "Collection.hpp"

class Simulation {
	private: 
		std::vector<Satellite> satelliteListe;
		std::vector<Collection> collectionListe;
		int nombreTour;

	public: 
		void parseData(const char *file);
};