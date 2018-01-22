#include "LapfChannel.h"


LapfChannel::~LapfChannel()
{
}

void LapfChannel::process(Packet packet)
{
	char* data = packet.getData();
	int size = packet.getSize();
	unsigned char lapf_size;
	unsigned char smallPack[256];
	//берем с третьего байта, т.к. первые 2 это номер канала а 3-ий размер пакета
	int position = 2;
	while ((size - Packet::crc_bytes - position) > 0)
	{
		lapf_size = data[position];
		position++;
		for (int i = position; i < position + lapf_size; i++)
		{
			smallPack[i - position] = data[i];
		}
		position += lapf_size;
		writeData(channel, smallPack, lapf_size);
	}
}
