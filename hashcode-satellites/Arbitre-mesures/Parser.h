#pragma once
#include "SatelliteArbitre.h"
#include "PicTaken.h"
#include "Collection.hpp"
#include <vector>
#include<map>

class Parser
{
private:
	std::map<int, SatelliteA> list_satellite_in;
	std::vector<PicTaken> list_pictaken;
	std::vector<Collection> list_collec;
	unsigned int nombreTour;
	unsigned int nombrePicTaken;

public:

	Parser();

	void parseData_in(const char *file);
	void parseData_out(const char *file);

	inline const std::map<int,SatelliteA>& getList_satellite_in()
	{
		return(list_satellite_in);
	}

	inline const std::vector<PicTaken>& getList_pictaken()
	{
		return(list_pictaken);
	}

	inline const std::vector<Collection>& getListCollec()
	{
		return list_collec;
	}

};