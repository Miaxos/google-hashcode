#pragma once

#include <vector>

typedef std::pair<int, int> Image;
typedef std::pair<unsigned int, unsigned int> Intervalle;

// Classe représentant une collection d'images
class Collection
{
    public:

        // Constructeur
        Collection(unsigned int points, unsigned int nbImages, unsigned int nbIntervalles);

        // Ajoute une image à la collection
        void addImage(int latitude, int longitude);

        // Ajoute un intervalle de temps à la collection
        void addIntervalle(unsigned int debut, unsigned int fin);

    private:

        unsigned int m_points;
        std::vector<Image> m_images;
        std::vector<Intervalle> m_intervalles;
};