#include "file_reader.h"
#include <fstream>
#include "stdafx.h"
#include <iostream>


using namespace std;

file_reader::file_reader()
{
	path = "1.ips";
}


file_reader::file_reader(string file)
{
	path = file;
}


file_reader::~file_reader()
{
}



void file_reader::test()
{
	//cout << path;
}