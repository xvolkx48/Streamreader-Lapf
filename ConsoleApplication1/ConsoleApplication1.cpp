#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstddef>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include "file_reader_bin.hpp"
#include "file_reader_ips.hpp"
#include "sort_lapf.hpp"
#include "my.h"
using namespace std;

vector<unsigned char>packet;
vector<unsigned char>packet2;
unsigned char buf[65536];


    string way_out = "out.ips";
	ofstream out(way_out, ios::app);
	


void LapF_pack_wrt(unsigned char *bufer, int L)
{
	
	for (int i = 0; i != L; i++)
	{
		out << bufer[i];
	}
//здесь из work класса my придут данные
//запись в файл подпакетов
	
}
shared_ptr<sort_lapf>Lapf_list(new sort_lapf(&LapF_pack_wrt));

int main()
{


	file_reader_ips qw("1.ips");
	way_out = "IP_STREAM";
	out.write(way_out.c_str(), way_out.length());
	//int buff=65535;
	short id = 0;
	int size_buf = 0;
	way_out = "IP_STREAM";
	out.write(way_out.c_str(), way_out.length());
	while (qw.eof())
	{
		size_buf = qw.read(buf);
		Lapf_list->SortLapf(buf, size_buf);

	}
}

 
/*
	Iter = id_list.begin();
	for (Iter; Iter!= id_list.end(); ++Iter)
	{
		out << hex << static_cast<int>((*Iter)->id_class)<<endl;
	}
	*/




//	unsigned char b0d0a[2];
//	b0d0a[0] = 0x0d;
//	b0d0a[1] = 0x0a;
//	char str[256];
//	int id;
//
//int len;
//unsigned char buf[65536];    
//FILE *in = fopen("1.ips", "rb");
//fread(buf, 1, 9, in);
//
//FILE *out = fopen("out.txt", "wb");
//
//while( fread(&len, 1, 4, in) == 4 )
//{
//	fread(buf, 1, len, in);
//
//
//	//itoa(len, str,10);
//	//fwrite(str, 1, strlen(str), out);
//	//fwrite(b0d0a, 1, 2, out);
//}
//
//fclose(in);


