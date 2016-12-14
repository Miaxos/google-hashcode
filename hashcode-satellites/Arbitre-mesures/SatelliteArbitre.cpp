#include "SatelliteArbitre.h"
#include <vector>


SatelliteA::SatelliteA(int latitude, int longitude, int vitLat, unsigned int orientMaxTour, unsigned int orientMaxTotal) :
	m_latitude(latitude),
	m_longitude(longitude),
	m_vitLat(vitLat),
	m_orientMaxTour(orientMaxTour),
	m_orientMaxTotal(orientMaxTotal),
	m_lastOrientLat(0),
	m_lastOrientLong(0),
	m_lastTurnPic(0)
{
}

vector<int>& SatelliteA::pos_tour(int i)
{
	vector<int> pos;
	
	if (i == 0)
	{
		pos={ SatelliteA::m_latitude, SatelliteA::m_longitude };
		return (pos);
	}
	else 
	{
		if (SatelliteA::m_latitude + SatelliteA::m_vitLat*(i - 1) <= 324000 || SatelliteA::m_latitude + SatelliteA::m_vitLat*(i - 1) >= 324000)
		{
			pos = { SatelliteA::m_latitude + (i - 1)*SatelliteA::m_vitLat,SatelliteA::m_longitude - 15 * (i - 1) };
			return(pos);
		}
		else
		{
			int lat = -(SatelliteA::m_latitude + (i - 1)*SatelliteA::m_vitLat) % 324000;
			pos = { lat,SatelliteA::m_longitude - 15 * (i - 1) };
			return(pos);
		}
	}
}

vector<int, int>& SatelliteA::orientLat_i(int i)
{
	vector<int, int> rangeLat;

	int minlat = 0;
	int maxlat = 0;

	if ((maxlat = m_lastOrientLat + m_orientMaxTour*(i - m_lastTurnPic)) > m_orientMaxTotal)
	{
		maxlat = m_orientMaxTotal;
	}

	if ((minlat = m_lastOrientLat + m_orientMaxTour*(i - m_lastTurnPic)) < -m_orientMaxTotal)
	{
		minlat = -m_orientMaxTotal;
	}

	rangeLat={ minlat,maxlat };
	return(rangeLat);

}

vector<int, int>& SatelliteA::orientLong_i(int i)
{
	vector<int, int> rangeLong;

	int minlong = 0;
	int maxlong = 0;

	if ((maxlong = m_lastOrientLong + m_orientMaxTour*(i - m_lastTurnPic)) > m_orientMaxTotal)
	{
		maxlong = m_orientMaxTotal;
	}

	if ((minlong = m_lastOrientLong + m_orientMaxTour*(i - m_lastTurnPic)) < -m_orientMaxTotal)
	{
		minlong = -m_orientMaxTotal;
	}

	rangeLong = { minlong,maxlong };
	return(rangeLong);
}

vector<int, int>& SatelliteA::rangeCamLat_i(int i)
{

	vector<int,int>& _pos_tour = { pos_tour(i) };
	vector<int,int>& rangeLat = { orientLat_i(i) };
	vector<int, int> rangeCam;

	rangeCam = { _pos_tour.at(0) + rangeLat.at(0),_pos_tour.at(0) + rangeLat.at(1) };

	return(rangeCam);

}

vector<int, int>& SatelliteA::rangeCamLong_i(int i)
{
	vector<int, int>& _pos_tour = { pos_tour(i) };
	vector<int, int>& rangeLong = { rangeCamLong_i(i) };

	vector<int, int> rangeCam = { _pos_tour.at(1) + rangeLong.at(0),_pos_tour.at(1) + rangeLong.at(1) };

	return(rangeCam);

}



std::ostream & operator<<(std::ostream & os, SatelliteA sat)
{
	os << "Satellite " << sat.getId() << endl;
}
