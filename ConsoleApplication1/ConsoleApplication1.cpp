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
	
	/*
	fwrite(&L_pac, 1, 4, out);
	fwrite(vagon, 1, 256, out);
	*/
	
}
shared_ptr<sort_lapf>Lapf_list(new sort_lapf(&LapF_pack_wrt));

int main()
{


	file_reader_ips qw("1.ips");
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