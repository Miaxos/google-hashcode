#pragma once

#include "Satellite.hpp"

class Photo
{
    friend void Satellite::prendrePhoto(Photo& photo, unsigned int tour);

    public:

        // Constructeur
        Photo(int latitude = 0, int longitude = 0);

    private:

        int m_latitude; // position de la photo en latitude
        int m_longitude; // position de la photo en longitude

        bool m_photoPrise; // vaut true si la photo a �t� prise par un satellite
        unsigned int m_idSatellitePhotographe; // L'id du satellite qui a pris la photo
        unsigned int m_tourPhoto; // le num�ro de tour pendant lequel la photo a �t� prise
};