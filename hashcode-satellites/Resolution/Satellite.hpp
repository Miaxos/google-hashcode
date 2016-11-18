#pragma once

#include <ostream>

// Classe mod�lisant un satellite
class Satellite
{
    friend std::ostream& operator<<(std::ostream& os, Satellite sat);

    public:

        // Constructeur
        Satellite(int latitude, int longitude, int vitLat, int orientMaxTour, int orientMaxTotal);

        /*
            D�place le satellite pour le faire passer au tour suivant
            Les param�tres d�finissent le d�placement souhait� en latitude et en longitude
            Si le d�placement est impossible, les valeurs max sont prises en compte � la place
        */
        void tourSuivant(int orientLat, int orientLong);

        static const int VIT_LONG = -15; // vitesse du satellite en longitude, correspondant � la vitesse de rotation de la Terre

    private:
    
        int m_latitude; // position du satellite en latitude
        int m_longitude; // position du satellite en longitude
        int m_vitLat; // vitesse du satellite en latitude

        int m_orientLat; // orientation en latitude
        int m_orientLong; // orientation en longitude
        int m_orientMaxTour; // changement d'orientation max par tour
        int m_orientMaxTotal; // orientation max totale
};

inline std::ostream& operator<<(std::ostream& os, Satellite sat)
{
    return os << "Position(" << sat.m_latitude << ", " << sat.m_longitude << ") ; Orientation(" << sat.m_orientLat << ", " << sat.m_orientLong << ") ; Vitesse " << sat.m_vitLat;
}