#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include "file_reader_bin.hpp"
#include "file_reader_ips.hpp"
#include "sort_lapf.hpp"
#include "my.h"
using namespace std;

unsigned char buf[65536];

const string output_file = "out.ips";
const string input_file = "1.ips";
const string file_header = "IP_STREAM";
	


void LapF_pack_wrt(unsigned char *bufer, int L)
{

	ofstream ofs(output_file, ios::app | ios::binary);
	if (!ofs)
		throw runtime_error("Cannot open ouput file");
	char size_byte[4];

	size_byte[0] = L & 0xFF;
	size_byte[1] = (L & 0xFF00) >> 8;
	size_byte[2] = (L & 0xFF0000) >> 16;
	size_byte[3] = (L & 0xFF000000) >> 32;

	ofs.write(size_byte, 4);

	//запись данных
	for (int i = 0; i != L; i++)
	{
		ofs << bufer[i];
	}

	ofs.close();
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
	cout << "\nPress enter to continue!";
	getch();
}