#include "Packet.h"
#include "IPStream.h"
#include <iostream>

using namespace std;

Packet::~Packet()
{
}

//�������� ������������� �� ����� ����������
bool Packet::isLapfPacket()
{
	if (((data[0] & 0x01) != 0) || ((data[1] & 0x01) != 1))  //��������� �������� ������ EA
		return false;
	int cur_size_position = 2; //3-� ���� - ��������� ����� ������� ������� ���������
	int lapf_sum_size = data[cur_size_position]; //������������� ����� �������� ���������� �������� ������� ���������
	int inner_data_size = size - lapf_header_bytes - lapf_size_bytes - crc_bytes; //������ ��������� ��� ������ ��������� �� ������� ���� ��������� ����������
	while (lapf_sum_size < inner_data_size) {						//���� ������, ������ ������ ���� ��� ��������
		cur_size_position += data[cur_size_position + 1];			//���� ������� ���������� ���������
		lapf_sum_size += data[cur_size_position];					//��������� � ����� ������ ���������� ���������
		inner_data_size -= lapf_size_bytes;											//�.�. ��������� ���� �������� - ��������� ���-�� ��������� ��� ������ ���� �� ���-�� ���� ������� ���������
	}
	if (lapf_sum_size != inner_data_size) //���� ��������� ������ ������ ���, �������� � ������, ������ ����� �����������
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

void Packet::getLapfPacket(vector<LapfPacket>& packets)
{
	
	char smallPack[256];
	int chanel = (data[0] & 0xFC) | ((data[1] & 0xF0) >> 4);
	unsigned char lapf_size;
	//����� � �������� �����, �.�. ������ 2 ��� ����� ������ � 3-�� ������ ������
	int position = 2;
	while ((size - crc_bytes - position) > 0)
	{
		lapf_size = data[position];
		position++;
		for (int i = position; i < position + lapf_size; i++)
		{
			smallPack[i - position] = data[i];
		}
		position += lapf_size;
		packets.push_back(LapfPacket(chanel, lapf_size, smallPack));
	}
}