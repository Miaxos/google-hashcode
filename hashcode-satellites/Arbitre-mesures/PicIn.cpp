#include "PicIn.hpp"

bool operator<(PicIn & p1, PicIn & p2)
{
	return(p1.getLat() < p2.getLat());
}

PicIn::PicIn(): 
	latitude(0),
	longitude(0)
{
}

PicIn::PicIn(int lat, int longit):
	latitude(lat),
	longitude(longit)
{
}

