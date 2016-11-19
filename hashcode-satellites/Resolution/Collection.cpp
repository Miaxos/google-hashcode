#include "Collection.hpp"
#include "ArgumentInvalideException.hpp"

Collection::Collection(unsigned int points, unsigned int nbImages, unsigned int nbIntervalles) :
    m_points(points),
    m_images(nbImages),
    m_intervalles(nbIntervalles)
{
    if(points > 10000)
    {
        throw ArgumentInvalideException("Le nombre de points doit etre compris entre 0 et 10000");
    }

    if(nbImages == 0 || nbImages > 100)
    {
        throw ArgumentInvalideException("Le nombre d'images doit etre compris entre 1 et 100");
    }

    if(nbImages == 0 || nbIntervalles > 100)
    {
        throw ArgumentInvalideException("Le nombre d'intervalles de temps doit etre compris entre 1 et 100");
    }
}

void Collection::addImage(int latitude, int longitude)
{
    if(latitude < -306000 || latitude > 306000)
    {
        throw ArgumentInvalideException("La latitude doit etre comprise entre -306000 et 306000");
    }

    if(longitude < -648000 || longitude > 647999)
    {
        throw ArgumentInvalideException("La longitude doit etre comprise entre -648000 et 647999");
    }

    m_images.push_back(Image(latitude, longitude));
}

void Collection::addIntervalle(unsigned int debut, unsigned int fin)
{
    if(fin < debut)
    {
        throw ArgumentInvalideException("La fin de l'intervalle doit etre situe apres le debut");
    }

    m_intervalles.push_back(Intervalle(debut, fin));
}