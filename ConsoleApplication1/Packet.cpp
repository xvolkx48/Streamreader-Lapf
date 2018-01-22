#include "Packet.h"
#include "IPStream.h"
#include <iostream>

using namespace std;

Packet::~Packet()
{
}

//проверка удовлетворяет ли пакет требования
bool Packet::isLapfPacket()
{
	if (((data[0] & 0x01) == 0) && ((data[1] & 0x01) == 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream &operator<<(ostream &os, const Packet &p)
{
	int size = p.getSize();
	char* data = p.getData();

	os << "Size: " << size << " Data: ";
	for (int i = 0; i<size; i++)
		os << data[i];
	return os;
}