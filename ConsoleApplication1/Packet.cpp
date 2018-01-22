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
	if (((data[0] & 0x01) != 0) || ((data[1] & 0x01) != 1))  //Проверяем значение байтов EA
		return false;
	int cur_size_position = 2; //3-й байт - положение байта размера первого подпакета
	int lapf_sum_size = data[cur_size_position]; //инициализация суммы размеров подпакетов размером первого подпакета
	int inner_data_size = size - lapf_header_bytes - lapf_size_bytes - crc_bytes; //размер доступный для данных подпакета за вычетом всей служебной информации
	while (lapf_sum_size < inner_data_size) {						//если меньше, значит должен быть ещё подпакет
		cur_size_position += data[cur_size_position + 1];			//байт размера следующего подпакета
		lapf_sum_size += data[cur_size_position];					//добавляем к сумме размер следующего подпакета
		inner_data_size -= lapf_size_bytes;											//т.к. добавился один подпакет - уменьшаем кол-во доступных для данных байт на кол-во байт размера подпакета
	}
	if (lapf_sum_size != inner_data_size) //если суммарный размер больше чем, доступно в пакете, значит пакет некорректен
		return false;
	
	return true;
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
