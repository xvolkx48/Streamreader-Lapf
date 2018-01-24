#include "LapfChannel.h"


LapfChannel::~LapfChannel()
{
}

void LapfChannel::process(Packet packet)
{
	char* data = packet.getData();		//�������� ������ �� ������
	int size = packet.getSize();		//�������� ������ ������
	unsigned char lapf_size;			//���������� ��� ������� ���������
	unsigned char smallPack[256];		//������ ��� ������ ���������
	//����� � �������� �����, �.�. ������ 2 ��� ����� ������ � 3-�� ������ ������
	int position = 2;					//������� ������� ��� ������ ������
	while ((size - Packet::crc_bytes - position) > 0)	//������ ������ �� Packet ���� ������� ������� �� ��������� ������� �������� ������, ����� ����������� 2 ��������� ����� �.�. ��� crc16 � ��� ��� �� �����
	{
		lapf_size = data[position];		//��������� ������ ���������
		position++;						//��������� ������� ������� �� ��������� ����
		//������������ ������ �� data � ������ ���������
		for (int i = position; i < position + lapf_size; i++)
		{
			smallPack[i - position] = data[i];
		}
		position += lapf_size;			//��������� ������� ������� � ����� ���������
		writeData(channel, smallPack, lapf_size);
	}
}
