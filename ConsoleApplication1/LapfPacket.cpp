#include "LapfPacket.h"


LapfPacket::LapfPacket(int c, unsigned char s, char* d)
{
	chanel = c;
	size = s;
	data = d;
}


LapfPacket::~LapfPacket()
{
}
