#include "LapfChannel.h"


LapfChannel::~LapfChannel()
{
}

void LapfChannel::process(Packet packet)
{
	char* data = packet.getData();		//получаем данные из пакета
	int size = packet.getSize();		//получаем размер пакета
	unsigned char lapf_size;			//переменная для размера подпакета
	unsigned char smallPack[256];		//массив для данных подпакета
	//берем с третьего байта, т.к. первые 2 это номер канала а 3-ий размер пакета
	int position = 2;					//текущая позиция для чтения данных
	while ((size - Packet::crc_bytes - position) > 0)	//читаем данные из Packet пока текущая позиция не привышает размера большого пакета, также отбрасываем 2 последних байта т.к. это crc16 и она нам не нужна
	{
		lapf_size = data[position];		//считываем размер подпакета
		position++;						//переводим текущую позицию на следующий байт
		//перечитываем данные из data в данные подпакета
		for (int i = position; i < position + lapf_size; i++)
		{
			smallPack[i - position] = data[i];
		}
		position += lapf_size;			//переводим текущую позицию в конец подпакета
		writeData(channel, smallPack, lapf_size);
	}
}
