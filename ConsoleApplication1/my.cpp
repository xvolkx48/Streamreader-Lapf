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
	unsigned char error = 0;
	int dl = 2; //3-� ���� - ��������� ����� ������� ������� ���������
	int L_sum = buff[dl]; // ����� �������� ���������� 
	int full_size = size_buff - 2 - 1 - 2; //����� �������� ������
	unsigned char vagon[65535];
	unsigned char L_pac = buff[dl];

	while (L_sum < full_size)//���� ������, ������ ������ ���� ��� ��������
	{
		for (int i = 0; i < L_pac; i++)
		{
			int r = 0;
			vagon[r] = buff[dl];
			r++;
		}

		Fdata(vagon, L_pac);

		dl += buff[dl] + 1;
		L_pac = buff[dl];
		L_sum += buff[dl];
		full_size -= 1;
	}
	if (L_sum != full_size)
	{
		error++;
	}

}
