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
