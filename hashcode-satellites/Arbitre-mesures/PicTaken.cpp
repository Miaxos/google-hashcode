#include "PicTaken.h"

PicTaken & PicTaken::operator<(PicTaken pic)
{
	return(turn < pic.getTurn() ? *this : pic);
}
