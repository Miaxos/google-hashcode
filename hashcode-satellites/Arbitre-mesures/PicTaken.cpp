#include "PicTaken.h"

bool operator<(PicTaken p1, PicTaken p2)
{
	return(p1.getTurn() < p2.getTurn());
}

std::ostream& operator<<(std::ostream & out, PicTaken pic)
{
	out << "Satellite " << pic.getId_Sat() << "[lat;long] : [ " << pic.getLatitude() << " ; " << pic.getLongitude() << " ]" << std::endl;
	return out;
}
