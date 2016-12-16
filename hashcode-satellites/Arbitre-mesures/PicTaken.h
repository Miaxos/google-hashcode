#pragma once


class PicTaken
{
private:
	int latitude;
	int longitude;
	int  id_sat;
	int turn;
public:
	PicTaken(int _latitude, int _longitude, int _id_sat, int _turn) : latitude(_latitude), longitude(_longitude),
		id_sat(_id_sat), turn(_turn) {};

};
