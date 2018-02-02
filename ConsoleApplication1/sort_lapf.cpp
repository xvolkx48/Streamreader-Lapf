#include"sort_lapf.hpp"
#include "stdafx.h"



sort_lapf::sort_lapf(TDataReady1 FDdata)
{
	Fdata = FDdata;
}

sort_lapf::~sort_lapf()
{
}
void sort_lapf::SortLapf(unsigned char * buff, int size_buff)
{
	if (((buff[0] & 0x01) == 0) && ((buff[1] & 0x01) == 1))
	{

		id_n = buff[0] & 0xFC;
		id_n <<= 2;
		id_n = id_n | ((buff[1] & 0xF0) >> 4);
		Iter_sort = id_list.begin();

		for (Iter_sort = id_list.begin(); Iter_sort != id_list.end(); Iter_sort++)
		{
			if ((*Iter_sort)->id_class == id_n)
			{
				//отдать функции класаа
				(*Iter_sort)->work(buff, size_buff);
				break;
			}
		}
		if (Iter_sort == id_list.end())
		{
			shared_ptr <my> new_my(new my(Fdata));
			new_my->id_class = id_n;
			id_list.push_back(new_my);
			Iter_sort--;
			(*Iter_sort)->work(buff, size_buff);
		}
	}

}