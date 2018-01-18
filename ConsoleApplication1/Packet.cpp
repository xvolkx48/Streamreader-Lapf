#include "Packet.h"
#include "IPStream.h"
#include <iostream>

using namespace std;

Packet::~Packet()
{
}


ostream &operator<<(ostream &os, const Packet &p)
{
	int size = p.getSize();
	char* data = p.getData();

	os << "Size: " << size << "Data: ";
	for (int i = 0; i<size; i++)
		os << data[i];
	return os;
}