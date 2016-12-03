#pragma once

#include <vector>
#include "Photo.hpp"

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
            m_images.push_back(Photo(latitude, longitude));
        }

        // Ajoute un intervalle de temps à la collection
        void addIntervalle(unsigned int debut, unsigned int fin);


        // Getters
        inline std::vector<Photo>& getImages()
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

    private:

        unsigned int m_points;
        std::vector<Photo> m_images;
        std::vector<Intervalle> m_intervalles;
};