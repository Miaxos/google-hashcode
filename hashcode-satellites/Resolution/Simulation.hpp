#pragma once
#include <vector>
#include "Photo.hpp"
#include "Collection.hpp"
using namespace std;

class Simulation {
	private: 
		vector<Satellite> satelliteListe;
		vector<Collection> collectionListe;
		int nombreTour;

	public: 
		void parseData(const char *file);
};