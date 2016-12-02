#pragma once

#include "Satellite.hpp"

class Photo
{
    friend void Satellite::prendrePhoto(Photo& photo, unsigned int tour);

    public:

        // Constructeur
        Photo(int latitude = 0, int longitude = 0);


        // Getters
        inline int getLatitude() const
        {
            return m_latitude;
        }

        inline int getLongitude() const
        {
            return m_longitude;
        }

        inline bool isPrise() const
        {
            return m_photoPrise;
        }

        inline unsigned int getIdSatellitePhotographe() const
        {
            return m_idSatellitePhotographe;
        }

        inline unsigned int getTourPhoto() const
        {
            return m_tourPhoto;
        }

    private:

        int m_latitude; // position de la photo en latitude
        int m_longitude; // position de la photo en longitude

        bool m_photoPrise; // vaut true si la photo a été prise par un satellite
        unsigned int m_idSatellitePhotographe; // L'id du satellite qui a pris la photo
        unsigned int m_tourPhoto; // le numéro de tour pendant lequel la photo a été prise
};