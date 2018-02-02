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
/*
vector<unsigned char>packet;
vector<unsigned char>packet2;
*/
unsigned char buf[65536];

const string output_file = "out.ips";
const string input_file = "1.ips";
const string file_header = "IP_STREAM";
	


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


	file_reader_ips qw(input_file);
	int size_buf = 0;
	ofstream ofs(output_file, ios::out | ios::binary);
	ofs.write(file_header.c_str(), file_header.length());
	ofs.close();
	while (qw.eof())
	{
		size_buf = qw.read(buf);
		Lapf_list->SortLapf(buf, size_buf);
	}
}