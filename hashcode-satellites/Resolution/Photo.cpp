#include "Photo.hpp"
#include "Collection.hpp"
#include "ArgumentInvalideException.hpp"

Photo::Photo(int latitude, int longitude) :
    m_photoPrise(false),
    m_latitude(latitude),
    m_longitude(longitude)
{
    if(latitude < -306000 || latitude > 306000)
    {
        throw ArgumentInvalideException("La latitude doit etre comprise entre -306000 et 306000");
    }

    if(longitude < -648000 || longitude > 647999)
    {
        throw ArgumentInvalideException("La longitude doit etre comprise entre -648000 et 647999");
    }
}

bool Photo::intervalleTempsOk(unsigned int tour)
{
    std::vector<Intervalle>& intervalles = m_collection->getIntervalles();

    for(Intervalle& i : intervalles)
    {
        if(tour >= i.first && tour <= i.second)
        {
            return true;
        }
    }

    return false;
}