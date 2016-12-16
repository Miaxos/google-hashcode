#pragma once

#include <vector>
#include "PicIn.hpp"
#include "PicTaken.h"

typedef std::pair<unsigned int, unsigned int> Intervalle;

// Classe représentant une collection d'images
class Collection
{
public:

	// Constructeur
	Collection(unsigned int points, unsigned int nbImages, unsigned int nbIntervalles);

	// Ajoute une image à la collection
	inline void addImage(int latitude, int longitude)
	{
		m_images.push_back(PicIn(latitude, longitude));
	}

	// Ajoute un intervalle de temps à la collection
	void addIntervalle(unsigned int debut, unsigned int fin);


	// Getters
	inline std::vector<PicIn>& getImages()
	{
		return m_images;
	}

	inline std::vector<Intervalle>& getIntervalles()
	{
		return m_intervalles;
	}

	inline unsigned int getPoints() const
	{
		return m_points;
	}


	//Fonctions de tests pour valider les collections
	bool rangeValid(PicTaken pic);

	bool posValid(PicTaken pic);

	void addPicValid();

	int collection_valid();

	void containPic(PicTaken pic);

	

private:

	unsigned int m_points;
	std::vector<PicIn> m_images;
	std::vector<Intervalle> m_intervalles;
	unsigned int nb_Image_Valid;
};