#pragma once
#include "Parser.h"
#include "PicTaken.h"
#include "SatelliteArbitre.h"
#include <algorithm>
#include <map>
#include <iterator>

class Arbitre
{
private:
	std::map<int,SatelliteA> list_satellite_in ;
	std::vector<PicTaken> list_pictaken;

public:
	Arbitre(std::map<int,SatelliteA> _list_satellite_in, std::vector<PicTaken> _list_pictaken);
	bool pictureValid(PicTaken pic);

	bool list_valid();


	Parser parser;


};