#include "SatelliteArbitre.h"
#include <vector>


SatelliteA::SatelliteA():
	m_latitude(0),
	m_longitude(0),
	m_vitLat(0),
	m_orientMaxTour(0),
	m_orientMaxTotal(0),
	m_lastOrientLat(0),
	m_lastOrientLong(0),
	m_lastTurnPic(0)
{
}

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
	pos.clear();
	
	if (i == 0)
	{
		pos.emplace_back(SatelliteA::m_latitude, SatelliteA::m_longitude );
		return (pos);
	}
	else 
	{
		if (SatelliteA::m_latitude + SatelliteA::m_vitLat*(i - 1) <= 324000 || SatelliteA::m_latitude + SatelliteA::m_vitLat*(i - 1) >= 324000)
		{
			pos.emplace_back(SatelliteA::m_latitude + (i - 1)*SatelliteA::m_vitLat,SatelliteA::m_longitude - 15 * (i - 1) );
			return(pos);
		}
		else
		{
			int lat = -(SatelliteA::m_latitude + (i - 1)*SatelliteA::m_vitLat) % 324000;
			pos.emplace_back(lat,SatelliteA::m_longitude - 15 * (i - 1) );
			return(pos);
		}
	}
}

vector<int>& SatelliteA::orientLat_i(int i)
{
	vector<int> rangeLat;

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

	rangeLat.emplace_back(minlat,maxlat );
	return(rangeLat);

}

vector<int>& SatelliteA::orientLong_i(int i)
{
	vector<int> rangeLong;

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

	rangeLong.emplace_back( minlong,maxlong );
	return(rangeLong);
}

vector<int>& SatelliteA::rangeCamLat_i(int i)
{

	vector<int> _pos_tour = pos_tour(i) ;
	vector<int>& rangeLat = orientLat_i(i) ;
	vector<int> rangeCam;

	rangeCam.emplace_back( _pos_tour.at(0) + rangeLat.at(0)  ,   _pos_tour.at(0) + rangeLat.at(1) );

	return(rangeCam);

}

vector<int>& SatelliteA::rangeCamLong_i(int i)
{
	vector<int>& _pos_tour = pos_tour(i) ;
	vector<int>& rangeLong =  rangeCamLong_i(i) ;

	vector<int> rangeCam = { _pos_tour.at(1) + rangeLong.at(0),_pos_tour.at(1) + rangeLong.at(1) };

	return(rangeCam);

}



std::ostream & operator<<(std::ostream & os, SatelliteA sat)
{
	os << "Satellite " << sat.getId() << endl;
}
