#include "Satellite.hpp"

Satellite::Satellite(int latitude, int longitude, int vitLat, int orientMaxTour, int orientMaxTotal) :
    m_latitude(latitude),
    m_longitude(longitude),
    m_vitLat(vitLat),
    m_orientMaxTour(orientMaxTour),
    m_orientMaxTotal(orientMaxTotal),
    m_orientLat(0),
    m_orientLong(0)
{ }

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
    orientLat = orientLat > m_orientMaxTour ? m_orientMaxTour : orientLat;
    orientLong = orientLong > m_orientMaxTour ? m_orientMaxTour : orientLong;

    m_orientLat += orientLat;
    m_orientLong += orientLong;

    m_orientLat = m_orientLat > m_orientMaxTotal ? m_orientMaxTotal : m_orientLat;
    m_orientLong = m_orientLong > m_orientMaxTotal ? m_orientMaxTotal : m_orientLong;
}