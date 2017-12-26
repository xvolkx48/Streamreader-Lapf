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
	int N = 10;
	int error = 0;
	
	int Len_index = 2;
	
	for (int k = 3; k < (size_buff - 2); k++)
	{
        if(error > N) return;
		unsigned char L = buff[Len_index];
		unsigned char bufer [65535];
		bufer[0] = (L+2);
	//	bufer[1] = id_n1;
		//bufer[2] = id_n2;
		if (Len_index <= (size_buff - 3 - 2))
		{

			for (int f = 0; f <= L; f++)//какой знак?
			{
				int r = 3;
				bufer[r] = buff[Len_index];
				r++;
			        Len_index++;
             }

			Fdata(bufer, L);
		
		}
		else
		{

			error++;

		}
	      
	}
	
}
