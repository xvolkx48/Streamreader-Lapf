#include"my.h"
#include "stdafx.h"
#include"sort_lapf.hpp"
my::my(TDataReady1 FDdata)
{
	Fdata = FDdata;
}
my::~my()
{
}
void my::work(unsigned char * buff, int size_buff)
{
	int dl = 2; //������� ������ � ������, ����� 3-� ���� - ��������� ����� ������� ������� ���������
	int L_sum = buff[dl]; // ����� �������� ���������� 
	int full_size = size_buff - 4; //����� �������� ������(2 ����� crc �����, 2 ����� id-������)
	unsigned char vagon[65535];
	unsigned char L_pac; //������ ���������

	while ((full_size-dl) > 0)//���� ������, ������ ������ ���� ��� ��������
	{
		L_pac = buff[dl];
		dl++;
		//���������� 2 ����� id ������ � ������ ���������
		vagon[0] = buff[0];
		vagon[1] = buff[1];
		for (int i = dl; i < dl+L_pac; i++)
		{
			vagon[i-dl] = buff[i];
		}
		//����������� ������ ��������� �� 2 �����(������ id ������)
		Fdata(vagon, L_pac+2);

		dl += L_pac;
	}
}
