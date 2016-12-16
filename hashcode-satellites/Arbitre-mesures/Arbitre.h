#pragma once
#include "PicTaken.h"
#include "SatelliteArbitre.h"
#include "Parser.h"
#include "Collection.hpp"
#include <algorithm>
#include <map>
#include <iterator>

class Arbitre
{

	
private:
	std::map<int,SatelliteA> list_satellite_in ;
	std::vector<PicTaken> list_pictaken;
	std::vector<Collection> list_collec;
	int score;

public:
	Arbitre(const char *file_in,const char *file_out);
	bool pictureValid(PicTaken& pic);

	bool list_valid();

	int& getScore();

};