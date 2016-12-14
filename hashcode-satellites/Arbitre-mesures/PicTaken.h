#pragma once


class PicTaken
{
	PicTaken& operator<(PicTaken pic);
private:
	int latitude;
	int longitude;
	int  id_sat;
	int turn;
public:
	PicTaken(int _latitude, int _longitude, int _id_sat, int _turn) : latitude(_latitude), longitude(_longitude),
		id_sat(_id_sat), turn(_turn) {};

	inline int getTurn()
	{
		return turn;
	}

	inline int getId_Sat()
	{
		return id_sat;
	}

	inline int getLatitude()
	{
		return latitude;
	}

	inline int getLongitude()
	{
		return longitude;
	}

};
