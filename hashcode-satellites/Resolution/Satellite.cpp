#include "Satellite.hpp"
#include "ArgumentInvalideException.hpp"

Satellite::Satellite(int latitude, int longitude, int vitLat, unsigned int orientMaxTour, unsigned int orientMaxTotal) :
    m_latitude(latitude),
    m_longitude(longitude),
    m_vitLat(vitLat),
    m_orientMaxTour(orientMaxTour),
    m_orientMaxTotal(orientMaxTotal),
    m_orientLat(0),
    m_orientLong(0)
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