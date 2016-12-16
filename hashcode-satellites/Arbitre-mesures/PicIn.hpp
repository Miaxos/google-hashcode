#pragma once
#include <vector>

using namespace std;


class PicIn 
{
	friend bool operator<(PicIn& p1, PicIn& p2);

private:
	int latitude;
	int longitude;

public:
	PicIn();
	PicIn(int lat, int longit);

	inline int& getLat()
	{
		return latitude;
	}

	inline int& getLong()
	{
		return longitude;
	}
	

};
