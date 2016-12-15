#pragma once

#include <ostream>
#include <vector>
#include "PicTaken.h"
using namespace std;

class SatelliteA
{
	friend std::ostream& operator<<(std::ostream& os, SatelliteA sat);

public:

	SatelliteA();
	SatelliteA(unsigned int id_sat,int latitude, int longitude, int vitLat, unsigned int orientMaxTour, unsigned int orientMaxTotal);

	//Position du satellite au tour i
	vector<int>& pos_tour(int i);

	//Intervale d'orientation de la caméra possible au tour i
	vector<int>& orientLat_i(int i);
	vector<int>& orientLong_i(int i);

	//Intervale de photo possible au tour i
	vector<int>& rangeCamLat_i(int i);
	vector<int>& rangeCamLong_i(int i);


	// Getters
	inline int getLastOrientLat() const
	{
		return m_lastOrientLat;
	}

	inline int getLastOrientLong() const
	{
		return m_lastOrientLong;
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


	int m_orientMaxTour; // changement d'orientation max par tour
	int m_orientMaxTotal; // orientation max totale
	int m_lastOrientLat; //Dernière orientation en latitude de la caméra
	int m_lastOrientLong; //Dernière orientation en longitude de la caméra
	int m_lastTurnPic; //Tour de la dernière photo prise

};
