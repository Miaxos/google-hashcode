#include "Arbitre.h"

Arbitre::Arbitre(std::map<int,SatelliteA> _list_satellite_in, std::vector<PicTaken> _list_pictaken) : 
	list_satellite_in(_list_satellite_in), 
	list_pictaken(_list_pictaken)
{
}

bool Arbitre::pictureValid(PicTaken pic)
{
	SatelliteA& sat = list_satellite_in[pic.getId_Sat()];

	if (pic.getLatitude() >= sat.rangeCamLat_i(pic.getTurn()).at(1) && pic.getLatitude() <= sat.rangeCamLat_i(pic.getTurn()).at(0))
	{
		return false;
	}

	if (pic.getLongitude() >= sat.rangeCamLong_i(pic.getTurn()).at(1) && pic.getLongitude() <= sat.rangeCamLong_i(pic.getTurn()).at(0))
	{
		return false;
	}

	return true;
}

bool Arbitre::list_valid()
{
	for (std::vector<PicTaken>::iterator it = list_pictaken.begin(); it != list_pictaken.end(); it++)
	{
		if (pictureValid(*it) == false)
		{
			return false;
		}
	}
	return true;
}
