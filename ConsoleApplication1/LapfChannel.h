#pragma once
#include "Packet.h"
typedef void(*WriteFunction)  (unsigned short channel, unsigned char *buff, int length);
class LapfChannel
{
public:
	LapfChannel(unsigned short c, WriteFunction w) :channel{ c }, writeData{ w } { };
	~LapfChannel();
	void process(Packet packet);
	unsigned short getChannel() const { return channel; };
private:
	unsigned short channel;
	WriteFunction writeData;
};

