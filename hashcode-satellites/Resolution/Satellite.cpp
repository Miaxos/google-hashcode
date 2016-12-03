#include "Satellite.hpp"
#include "ArgumentInvalideException.hpp"
#include "Photo.hpp"
#include <algorithm>

unsigned int Satellite::m_idCount = 0; // le premier satellite créé aura l'id 0

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
    // Déplacement

    int latTemp = m_latitude + m_vitLat;

    // si on reste entre -90 et +90 degrés
    if(latTemp >= -324000 && latTemp <= 324000)
    {
        m_latitude = latTemp;
        m_longitude += VIT_LONG;
    }
    // si on passe derrière un des pôles
    else
    {
        m_longitude = -648000 + (m_longitude + VIT_LONG);
        m_vitLat *= -1;

        // si on passe derrière le pôle nord
        if(latTemp > 324000)
        {
            m_latitude = 648000 - latTemp;
        }
        // si on passe derrière le pôle sud
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

    // on vérifie qu'on ne dépasse pas l'intervalle max pour le tour
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

    // on vérifie qu'on ne dépasse pas l'intervalle total max
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
    if(!photo.m_photoPrise)
    {
        photo.m_idSatellitePhotographe = m_id;
        photo.m_tourPhoto = tour;
		photo.m_photoPrise = true;
    }
}

EtatSatellitePhoto Satellite::prochainePhoto(const std::vector<Photo*>& photos, unsigned int tourMax)
{
    EtatSatellitePhoto etat;
    etat.photo = nullptr;

    unsigned int tour = 0;
    int orientLatMin = m_orientLat, orientLatMax = m_orientLat;
    int orientLongMin = m_orientLong, orientLongMax = m_orientLong;
    int latitude = m_latitude, longitude = m_longitude;
    int vitLat = m_vitLat;

    bool trouve = false;

    while(!trouve && tour <= tourMax)
    {
        tour++;

        // calcul des intervalles pour les orientations
        auto majOrient = [this] (int& orient, char signe) -> void
        {
            int orientMaxTotal = m_orientMaxTotal * signe;

            if(orient != orientMaxTotal)
            {
                orient += m_orientMaxTour * signe;
                if(abs(orient) > abs(orientMaxTotal))
                {
                    orient = orientMaxTotal;
                }
            }
        };

        majOrient(orientLatMin, -1);
        majOrient(orientLatMax, 1);
        majOrient(orientLongMin, -1);
        majOrient(orientLongMax, 1);

        // répétition avec la méthode Satellite::tourSuivant, il faudrait optimiser ou supprimer une des deux

        // Déplacement

        int latTemp = latitude + vitLat;

        // si on reste entre -90 et +90 degrés
        if(latTemp >= -324000 && latTemp <= 324000)
        {
            latitude = latTemp;
            longitude += VIT_LONG;
        }
        // si on passe derrière un des pôles
        else
        {
            longitude = -648000 + (longitude + VIT_LONG);
            vitLat *= -1;

            // si on passe derrière le pôle nord
            if(latTemp > 324000)
            {
                latitude = 648000 - latTemp;
            }
            // si on passe derrière le pôle sud
            else
            {
                latitude = -648000 - latTemp;
            }
        }

        std::pair<int, int> intervalleLat(latitude + orientLatMin, latitude + orientLatMax);
        std::pair<int, int> intervalleLong(longitude + orientLongMin, longitude + orientLongMax);

        // recherche dichotomique
        int debut = 0, fin = photos.size() - 1, milieu;

        while(!trouve && debut <= fin)
        {
            milieu = (debut + fin) / 2;
            if(photos[milieu]->getLatitude() >= intervalleLat.first && photos[milieu]->getLatitude() <= intervalleLat.second
                && photos[milieu]->getLongitude() >= intervalleLong.first && photos[milieu]->getLongitude() <= intervalleLong.second)
            {
                trouve = true;
                etat.photo = photos[milieu];
                etat.tour = tour;
                etat.orientLat = latitude - photos[milieu]->getLatitude();
                etat.orientLong = longitude - photos[milieu]->getLongitude();
            }
            else if(intervalleLat.first < photos[milieu]->getLatitude())
            {
                debut = milieu + 1;
            }
            else
            {
                fin = milieu - 1;
            }
        }
    }

    return etat;
}