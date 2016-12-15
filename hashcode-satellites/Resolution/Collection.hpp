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

		// Modification du ratio 
		void setRatio(int nbToursRestants) {
			if (nbPhotosRestantes == 0 || nbToursRestants == 0) {
				ratioEfficacite = 0;
			}
			else {
				ratioEfficacite = m_points / (nbPhotosRestantes*nbToursRestants);
			}
		}

		// Setteurs
		void setNbPhotosRestantes() {
			nbPhotosRestantes--;
		}

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

		inline double getRatio() const {
			return ratioEfficacite;
		}

		inline int getPhotosRestantes() const{
			return nbPhotosRestantes;
		}

    private:

        unsigned int m_points;
        std::vector<Photo> m_images;
        std::vector<Intervalle> m_intervalles;
		double ratioEfficacite;
		unsigned int nbPhotosRestantes;
};