#include "LapfVault.h"

LapfVault::~LapfVault()
{
}

unsigned short LapfVault::getChannel(Packet packet)
{
	char* data = packet.getData();
	int channel = ((data[0] & 0xFC)<<2) | (((data[1] & 0xF0) >> 4));
	return channel;
}

void LapfVault::process(Packet packet)
{
	unsigned short channel = getChannel(packet);
	channels_iterator = channels_list.begin();

	for (channels_iterator = channels_list.begin(); channels_iterator != channels_list.end(); channels_iterator++)
	{
		if ((*channels_iterator)->getChannel() == channel)
		{
			(*channels_iterator)->process(packet);
			break;
		}
	}
	if (channels_iterator == channels_list.end())
	{
		shared_ptr <LapfChannel> new_channel(new LapfChannel(channel, writeData));
		channels_list.push_back(new_channel);
		channels_iterator--;
		(*channels_iterator)->process(packet);
	}
}

