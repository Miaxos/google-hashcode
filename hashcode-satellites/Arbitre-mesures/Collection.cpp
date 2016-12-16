#include "Collection.hpp"
#include "ArgumentInvalideException.hpp"

Collection::Collection(unsigned int points, unsigned int nbImages, unsigned int nbIntervalles) :
	m_points(points),
	nb_Image_Valid(0)
{
	if (points > 10000)
	{
		throw ArgumentInvalideException("Le nombre de points doit etre compris entre 0 et 10000");
	}

	if (nbImages == 0 || nbImages > 100)
	{
		throw ArgumentInvalideException("Le nombre d'images doit etre compris entre 1 et 100");
	}

	if (nbImages == 0 || nbIntervalles > 100)
	{
		throw ArgumentInvalideException("Le nombre d'intervalles de temps doit etre compris entre 1 et 100");
	}

	m_images.reserve(nbImages);
	m_intervalles.reserve(nbIntervalles);
}

void Collection::addIntervalle(unsigned int debut, unsigned int fin)
{
	if (fin < debut)
	{
		throw ArgumentInvalideException("La fin de l'intervalle doit etre situe apres le debut");
	}

	m_intervalles.push_back(Intervalle(debut, fin));
}

bool Collection::rangeValid(PicTaken pic)
{
	for (auto it = m_intervalles.begin(); it != m_intervalles.end(); it++)
	{
		if (pic.getTurn() >= (*it).first && pic.getTurn() <= (*it).second)
		{
			return true;
		}
	}
	return false;
}

bool Collection::posValid(PicTaken pic)
{
	for (auto it = m_images.begin(); it != m_images.end(); it++)
	{
		if (pic.getLatitude() == (*it).getLat() && pic.getLongitude() == (*it).getLong())
			return true;
	}
	return false;
}

void Collection::addPicValid()
{
	nb_Image_Valid++;
}

int Collection::collection_valid()
{
	return(nb_Image_Valid == m_images.size()?	m_points: 0);
}

void Collection::containPic(PicTaken pic)
{
	if (posValid(pic) && rangeValid(pic))
	{
		addPicValid();
	}
}

