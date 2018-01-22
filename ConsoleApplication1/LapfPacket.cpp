#include "LapfPacket.h"


LapfPacket::~LapfPacket()
{
}

ostream& operator<<(ostream& os, LapfPacket pack)
{
	int size = pack.getSize();
	char* data = pack.getData();
	os << "Channel: " << pack.getChannel()
		<< "\nSize: " << size
		<< "\nData: ";
	for (int i = 0; i < size; i++)
		os << data[i];
	os << "\n";
	return os;
}

ostream& operator<<(ostream& os, vector<LapfPacket> packets) 
{
	for (int i = 0; i < packets.size(); i++)
		os << packets[i];
	return os;
}