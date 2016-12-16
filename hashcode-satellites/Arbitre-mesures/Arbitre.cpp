#include "Arbitre.h"

Arbitre::Arbitre(const char *file_in, const char *file_out):
	score(0)
{
	Parser p;
	p.parseData_in(file_in);
	p.parseData_out(file_out);
	//Duplique les listes, à corriger si on a le temps
	list_satellite_in = move(p.getList_satellite_in());
	list_pictaken = move(p.getList_pictaken());
	list_collec = move(p.getListCollec());


	

	std::sort(list_pictaken.begin(), list_pictaken.end());

	for (auto it = list_pictaken.begin(); it != list_pictaken.end(); it++)
	{
		pictureValid(*it);
	}

}

bool Arbitre::pictureValid(PicTaken& pic)
{
	SatelliteA& sat = list_satellite_in[pic.getId_Sat()];
	if (pic.getLatitude() >= sat.rangeCamLat_i(pic.getTurn()).at(0) && pic.getLatitude() <= sat.rangeCamLat_i(pic.getTurn()).at(1))
	{
		return false;
	}

	if (pic.getLongitude() >= sat.rangeCamLong_i(pic.getTurn()).at(0) && pic.getLongitude() <= sat.rangeCamLong_i(pic.getTurn()).at(1))
	{
		return false;
	}

	for (auto it = list_collec.begin(); it != list_collec.end(); it++)
	{
		//Test pour savoir si la photo appartient à une collection, et ajoute la photo à chaque collection si oui
		(*it).containPic(pic);
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

int& Arbitre::getScore()
{
	for (auto it = list_collec.begin(); it != list_collec.end(); it++)
	{
		score+= (*it).collection_valid();
	}
	return score;
}


