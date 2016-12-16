#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

Parser::Parser()
{
	list_satellite_in.clear();
	list_pictaken.clear();
}

void Parser::parseData_in(const char * file)
{
	ifstream dataFile;
	dataFile.open(file);


	if (!dataFile.is_open())
	{
		cerr << "Erreur : impossible d'ouvrir le fichier " << file << " en lecture" << endl;
		exit(EXIT_FAILURE);
	}

	int id_sat = 0;
	string line;
	unsigned int lineCounter = 1;
	getline(dataFile, line);
	Parser::nombreTour = stoi(line);
	lineCounter++;
	getline(dataFile, line);

	// Ajout des satellites
	const unsigned int satelliteNumber = stoi(line);
	lineCounter++;
	for (unsigned int i = lineCounter; i < lineCounter + satelliteNumber; i++) 
	{
		getline(dataFile, line);
		istringstream splitStream(line);
		string splitString;
		vector<string> contenuLigne;
		while (getline(splitStream, splitString, ' ')) {
			contenuLigne.push_back(splitString);
		}
		int latitudeSat = stoi(contenuLigne.at(0));
		int longitudeSat = stoi(contenuLigne.at(1));
		int vitLatSat = stoi(contenuLigne.at(2));
		int orientMaxTourSat = stoi(contenuLigne.at(3));
		int orientMaxTotalSat = stoi(contenuLigne.at(4));
		SatelliteA s(id_sat,latitudeSat, longitudeSat, vitLatSat, orientMaxTourSat, orientMaxTotalSat);
		Parser::list_satellite_in[s.getId()]=s;
		id_sat++;
	}
	lineCounter += satelliteNumber;

	// Ajout des collections
	getline(dataFile, line);
	const unsigned int collectionNumber = stoi(line);
	lineCounter++;
	for (unsigned int j = 0; j < collectionNumber; j++)
	{
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
		list_collec.push_back(c);
	}
}


void Parser::parseData_out(const char * file)
{
	ifstream dataFile;
	dataFile.open(file);

	if (!dataFile.is_open())
	{
		cerr << "Erreur : impossible d'ouvrir le fichier " << file << " en lecture" << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	unsigned int lineCounter = 1;
	getline(dataFile, line);
	Parser::nombrePicTaken = stoi(line);
	lineCounter++;

	for (unsigned int i = lineCounter; i < lineCounter + nombrePicTaken; i++)
	{
		getline(dataFile, line);
		istringstream splitStream(line);
		string splitString;
		vector<string> contenuLigne;
		while (getline(splitStream, splitString, ' ')) {
			contenuLigne.push_back(splitString);
		}
		int latitude = stoi(contenuLigne.at(0));
		int longitude = stoi(contenuLigne.at(1));
		int turn = stoi(contenuLigne.at(2));
		int id_sat = stoi(contenuLigne.at(3));
		PicTaken pic(latitude, longitude, id_sat, turn);
		list_pictaken.push_back(pic);

	}

}
