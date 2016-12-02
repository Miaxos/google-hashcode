#include "Photo.hpp"
#include "ArgumentInvalideException.hpp"

Photo::Photo(int latitude, int longitude) :
    m_photoPrise(false)
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