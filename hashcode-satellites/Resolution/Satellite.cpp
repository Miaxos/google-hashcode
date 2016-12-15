#include "Satellite.hpp"
#include "ArgumentInvalideException.hpp"
#include "Photo.hpp"
#include "Collection.hpp"
#include <algorithm>
#include <iostream>

unsigned int Satellite::m_idCount = 0; // le premier satellite cr�� aura l'id 0

Satellite::Satellite(int latitude, int longitude, int vitLat, unsigned int orientMaxTour, unsigned int orientMaxTotal) :
    m_latitude(latitude),
    m_longitude(longitude),
    m_vitLat(vitLat),
    m_orientMaxTour(orientMaxTour),
    m_orientMaxTotal(orientMaxTotal),
    m_orientLat(0),
    m_orientLong(0),
    m_id(m_idCount)
{
    if(latitude < -324000 || latitude > 324000)
    {
        throw ArgumentInvalideException("La latitude doit etre comprise entre -324000 et 324000");
    }

    if(longitude < -648000 || longitude > 647999)
    {
        throw ArgumentInvalideException("La longitude doit etre comprise entre -648000 et 647999");
    }

    if(abs(vitLat) < 100 || abs(vitLat) > 500)
    {
        throw ArgumentInvalideException("La valeur absolue de la vitesse en latitude doit etre comprise entre 100 et 500");
    }

    if(orientMaxTour < 0 || orientMaxTour > 200)
    {
        throw ArgumentInvalideException("Le changement d'orientation maximum par tour doit etre compris entre 0 et 200");
    }

    if(orientMaxTotal < 0 || orientMaxTotal > 10000)
    {
        throw ArgumentInvalideException("L'orientation maximale totale doit etre comprise entre 0 et 10000");
    }

    m_idCount++;
}

void Satellite::tourSuivant(int orientLat, int orientLong)
{
    // D�placement

    int latTemp = m_latitude + m_vitLat;

    // si on reste entre -90 et +90 degr�s
    if(latTemp >= -324000 && latTemp <= 324000)
    {
        m_latitude = latTemp;
        m_longitude += VIT_LONG;
    }
    // si on passe derri�re un des p�les
    else
    {
        m_longitude = -648000 + (m_longitude + VIT_LONG);
        m_vitLat *= -1;

        // si on passe derri�re le p�le nord
        if(latTemp > 324000)
        {
            m_latitude = 648000 - latTemp;
        }
        // si on passe derri�re le p�le sud
        else
        {
            m_latitude = -648000 - latTemp;
        }
    }

    // si on a fait le tour de la Terre
    if(m_longitude < -648000)
    {
        m_longitude = 648000 + (m_longitude + 648000);
    }


    // Orientation

    // on v�rifie qu'on ne d�passe pas l'intervalle max pour le tour
    if(orientLat > m_orientMaxTour)
    {
        m_orientLat += m_orientMaxTour;
    }
    else if(orientLat < -m_orientMaxTour)
    {
        m_orientLat -= m_orientMaxTour;
    }
    else
    {
        m_orientLat += orientLat;
    }

    if(orientLong > m_orientMaxTour)
    {
        m_orientLong += m_orientMaxTour;
    }
    else if(orientLong < -m_orientMaxTour)
    {
        m_orientLong -= m_orientMaxTour;
    }
    else
    {
        m_orientLong += orientLong;
    }

    // on v�rifie qu'on ne d�passe pas l'intervalle total max
    if(m_orientLat > m_orientMaxTotal)
    {
        m_orientLat = m_orientMaxTotal;
    }
    else if(m_orientLat < -m_orientMaxTotal)
    {
        m_orientLat = -m_orientMaxTotal;
    }

    if(m_orientLong > m_orientMaxTotal)
    {
        m_orientLong = m_orientMaxTotal;
    }
    else if(m_orientLong < -m_orientMaxTotal)
    {
        m_orientLong = -m_orientMaxTotal;
    }
}

void Satellite::prendrePhoto(Photo& photo, unsigned int tour)
{
    if(photo.getLatitude() == m_latitude + m_orientLat && photo.getLongitude() == m_longitude + m_orientLong)

    {
        if(!photo.m_photoPrise)
        {
            photo.m_idSatellitePhotographe = m_id;
            photo.m_tourPhoto = tour;
            photo.m_photoPrise = true;
			photo.m_collection->setNbPhotosRestantes();
        }
    }
}

EtatSatellitePhoto Satellite::prochainePhoto(const std::vector<Photo*>& photos, unsigned int tourCourant, unsigned int tourMax)
{
    EtatSatellitePhoto etat;
    etat.photo = nullptr;

    int orientLatMin = m_orientLat, orientLatMax = m_orientLat;
    int orientLongMin = m_orientLong, orientLongMax = m_orientLong;
    int latitude = m_latitude, longitude = m_longitude;
    int vitLat = m_vitLat;
	int seuil = 0;
    bool trouve = false;
	const int tour = tourCourant;

    while(!trouve && tourCourant <= tourMax)
    {
        tourCourant++;

        // calcul des intervalles pour les orientations
        auto majOrient = [this] (int& orient, char signe) -> void
        {
            int orientMaxTotal = m_orientMaxTotal * signe;

            if(orient != orientMaxTotal)
            {
                orient += m_orientMaxTour * signe;
                if(abs(orient) > m_orientMaxTotal)
                {
                    orient = orientMaxTotal;
                }
            }
        };

        majOrient(orientLatMin, -1);
        majOrient(orientLatMax, 1);
        majOrient(orientLongMin, -1);
        majOrient(orientLongMax, 1);

        // r�p�tition avec la m�thode Satellite::tourSuivant, il faudrait optimiser ou supprimer une des deux

        // D�placement

        int latTemp = latitude + vitLat;

        // si on reste entre -90 et +90 degr�s
        if(latTemp >= -324000 && latTemp <= 324000)
        {
            latitude = latTemp;
            longitude += VIT_LONG;
        }
        // si on passe derri�re un des p�les
        else
        {
            longitude = -648000 + (longitude + VIT_LONG);
            vitLat *= -1;

            // si on passe derri�re le p�le nord
            if(latTemp > 324000)
            {
                latitude = 648000 - latTemp;
            }
            // si on passe derri�re le p�le sud
            else
            {
                latitude = -648000 - latTemp;
            }
        }

        // si on a fait le tour de la Terre
        if(longitude < -648000)
        {
            longitude = 648000 + (longitude + 648000);
        }

        // calcul des intervalles de positions que la cam�ra peut atteindre
        std::pair<int, int> intervalleLat(latitude + orientLatMin, latitude + orientLatMax);
        std::pair<int, int> intervalleLong(longitude + orientLongMin, longitude + orientLongMax);

        // au-dessus de 85� nord ou sud (306000 ou -306000), on sait qu'il n'y aura pas de photo
        if(intervalleLat.first >= 306000 || intervalleLat.second <= -306000)
        {
            continue;
        }

		while (!trouve) {
			for (Photo* p : photos)
			{
				// si on a trouv� une photo, on s'arr�te
				if (p->intervallePositionOk(intervalleLat.first, intervalleLat.second, intervalleLong.first, intervalleLong.second) &&
					!p->isPrise() && p->intervalleTempsOk(tourCourant) && seuil > tourCourant - tour)
				{
					trouve = true;
					etat.photo = p;
					etat.tour = tourCourant;
					etat.orientLat = p->getLatitude() - latitude;
					etat.orientLong = p->getLongitude() - longitude;

					return etat;
				}
			}
			if (seuil < tourMax) {
				seuil += 100;
			}
			else {
				break;
			}
			
		}
		
    }

    return etat;
}