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
	int dl = 2; //позиция чтения в пакете, берем 3-й байт - положение байта размера первого подпакета
	int L_sum = buff[dl]; // сумма размеров подпакетов 
	int full_size = size_buff - 4; //длина большого пакета(2 байта crc сумма, 2 байта id-канала)
	unsigned char vagon[65535];
	unsigned char L_pac; //размер подпакета

	while ((full_size-dl) > 0)//если меньше, значит должен быть ещё подпакет
	{
		L_pac = buff[dl];
		dl++;
		for (int i = dl; i < dl+L_pac; i++)
		{
			vagon[i-dl] = buff[i];
		}

		Fdata(vagon, L_pac);

		dl += L_pac;
	}
}
