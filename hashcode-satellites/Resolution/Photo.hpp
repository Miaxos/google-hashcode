#pragma once

#include "Satellite.hpp"

class Collection;

class Photo
{
    friend void Satellite::prendrePhoto(Photo& photo, unsigned int tour);

    public:

        // Constructeur
        Photo(int latitude = 0, int longitude = 0);

        /*
            Retourne true s'il est possible de prendre la photo au tour passé en paramètre
            par rapport aux intervalles de temps définis pour la collection
        */
        bool intervalleTempsOk(unsigned int tour);

        // Retourne true si l'image est positionnée dans le rectangle formé par les 4 paramètres
        bool intervallePositionOk(int latitudeMin, int latitudeMax, int longitudeMin, int longitudeMax);

        // Retourne true si la latitude de l'image est comprise dans l'intervalle donné
        bool intervalleLatitudeOk(int latitudeMin, int latitudeMax);

        // Retourne true si la longitude de l'image est comprise dans l'intervalle donné
        bool intervalleLongitudeOk(int longitudeMin, int longitudeMax);


        //Setters
        inline void setCollection(Collection* collection)
        {
            m_collection = collection;
        }


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

        Collection* m_collection; // pointeur vers la collection dont la photo fait partie

        int m_latitude; // position de la photo en latitude
        int m_longitude; // position de la photo en longitude

        bool m_photoPrise; // vaut true si la photo a été prise par un satellite
        unsigned int m_idSatellitePhotographe; // L'id du satellite qui a pris la photo
        unsigned int m_tourPhoto; // le numéro de tour pendant lequel la photo a été prise
};