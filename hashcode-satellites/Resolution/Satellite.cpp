#include "Satellite.hpp"
#include "ArgumentInvalideException.hpp"

Satellite::Satellite(int latitude, int longitude, int vitLat, int orientMaxTour, int orientMaxTotal) :
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
    orientLat = orientLat > m_orientMaxTour ? m_orientMaxTour : orientLat;
    orientLong = orientLong > m_orientMaxTour ? m_orientMaxTour : orientLong;

    m_orientLat += orientLat;
    m_orientLong += orientLong;

    m_orientLat = m_orientLat > m_orientMaxTotal ? m_orientMaxTotal : m_orientLat;
    m_orientLong = m_orientLong > m_orientMaxTotal ? m_orientMaxTotal : m_orientLong;
}