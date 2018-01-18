#include "Packet.h"
#include "IPStream.h"


Packet::Packet(int s, char* d)
{
	size = s;
	data = d;
}


Packet::~Packet()
{
}

IPStream& operator>>(IPStream& ips, Packet& packet)
{
	int size = ips.getPacketSize();
	char buffer[65535];
	ips.getPacket(buffer, size);

}

//Packet packet;
//IPStream ips("1.ips");
//ips >> packet;

//Packet IPStream::get()
//{
//	int size = getPacketSize();
//	char buffer[65535];
//	getPacket(buffer, size);
//	return Packet{ size, buffer };
//}
//
//IPStream ips("1.ips");
//Packet packet{ ips.get() };