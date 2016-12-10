#pragma once

#include <ostream>
#include <vector>
using namespace std;

class Satellite
{
	friend std::ostream& operator<<(std::ostream& os, Satellite sat);

public:

	Satellite(int latitude, int longitude, int vitLat, unsigned int orientMaxTour, unsigned int orientMaxTotal);

	//Position du satellite au tour i
	vector<int> pos_tour(int i);

	// Getters
	inline int getOrientLat() const
	{
		return m_orientLat;
	}

	inline int getOrientLong() const
	{
		return m_orientLong;
	}

	inline unsigned int getId() const
	{
		return m_id;
	}

	static const int VIT_LONG = -15; /*Vitesse du satellite en longitude, correspondant à la vitesse 
	de rotation de la Terre*/

private:

	static unsigned int m_idCount;

	unsigned int m_id; // l'id du satellite

	int m_latitude; // position du satellite en latitude
	int m_longitude; // position du satellite en longitude
	int m_vitLat; // vitesse du satellite en latitude

	int m_orientLat; // orientation en latitude
	int m_orientLong; // orientation en longitude
	int m_orientMaxTour; // changement d'orientation max par tour
	int m_orientMaxTotal; // orientation max totale
};
