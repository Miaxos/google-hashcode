#pragma once
#include "Satellite.h"
#include <vector>

class Parser
{
private:
	std::vector<Satellite> list_satellite_in;
	std::vector<Satellite> list_satellite_in;
	unsigned int nombreTour;

public:
	void parseData_in(const char *file);
	void parseData_out(const char *file);

};