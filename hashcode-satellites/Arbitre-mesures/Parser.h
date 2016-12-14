#pragma once
#include "SatelliteArbitre.h"
#include "PicTaken.h"
#include <vector>
#include<map>

class Parser
{
private:
	std::map<int,SatelliteA> list_satellite_in;
	std::vector<PicTaken> list_pictaken;
	unsigned int nombreTour;
	unsigned int nombrePicTaken;

public:
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

};