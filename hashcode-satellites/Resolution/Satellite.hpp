#pragma once

#include <ostream>
#include <vector>

class Photo;

struct EtatSatellitePhoto
{
    Photo* photo; // Pointeur vers la photo
    unsigned int tour;
    int orientLat;
    int orientLong;
};

// Classe mod�lisant un satellite
class Satellite
{
    friend std::ostream& operator<<(std::ostream& os, Satellite sat);

    public:

        // Constructeur, lance une exception si un argument a une valeur invalide
        Satellite(int latitude, int longitude, int vitLat, unsigned int orientMaxTour, unsigned int orientMaxTotal);

        /*
            D�place le satellite pour le faire passer au tour suivant
            Les param�tres d�finissent le d�placement souhait� en latitude et en longitude
            Si le d�placement est impossible, les valeurs max sont prises en compte � la place
        */
        void tourSuivant(int orientLat, int orientLong);

        // Indique que le satellite prend la photo donn�e au tour donn�
        void prendrePhoto(Photo& photo, unsigned int tour);

        // Recherche la prochaine photo qui peut �tre prise et indique � quel tour elle peut �tre prise
        // Pr�-condition : les photos sont tri�es
        EtatSatellitePhoto prochainePhoto(const std::vector<Photo*>& photos, unsigned int tourCourant, unsigned int tourMax);
    
    void instancierTab(std::vector<std::vector<Photo*>> &tabs, const std::vector<Photo*>& photos, unsigned int tourMax, std::vector<int> &idtab);


        // Getters
        inline int getOrientLat() const
        {
            return m_orientLat;
        }

        inline int getOrientLong() const
        {
            return m_orientLong;
        }
    
    inline int getLat() const
    {
        return m_latitude;
    }
    inline int getLong() const
    {
        return m_longitude;
    }
    inline int getOrientMaxTour() const
    {
        return m_orientMaxTour;
    }
    inline int getOrientMaxTotal() const
    {
        return m_orientMaxTotal;
    }

        inline unsigned int getId() const
        {
            return m_id;
        }

        static const int VIT_LONG = -15; // vitesse du satellite en longitude, correspondant � la vitesse de rotation de la Terre
    std::vector<std::vector<Photo*>> pointspossibles; // List des pts possibles pour les satellites

    private:

        static unsigned int m_idCount;
    
        unsigned int m_id; // l'id du satellite

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
