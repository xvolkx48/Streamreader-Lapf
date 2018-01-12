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

string out_file = "out.ips";
ofstream out(out_file, ios::app);

/*
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
*/
int main()
{
	string head_file;
	file_reader_ips qw("1.ips");
	short id = 0;
	int size_buf = 0;
	head_file = "IP_STREAM";
	out.write(head_file.c_str(), head_file.length());
	while (qw.eof())
	{
		size_buf = qw.read(buf);
//		Lapf_list->SortLapf(buf, size_buf);
	}
}



