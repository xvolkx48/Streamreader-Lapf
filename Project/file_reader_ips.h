#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "file_reader_bin.h"
using namespace std;
class file_reader_ips
{
	file_reader_bin p;
public:
	file_reader_ips(string fileway)
	{
		p.open(fileway);
		p.seekg(9);
	}
	unsigned read(unsigned char* data)
	{
		int i = 0;
		int sizepaket = 0;
		p.read(reinterpret_cast<unsigned char*>(&sizepaket), 4);
		if (sizepaket == 0)
		{
			data = { 0 };
			return 0;
		}
		p.read(data, sizepaket);
		return sizepaket;
	}
	unsigned read(vector<unsigned char> &dat)
	{
		int i = 0;
		int sizepaket = 0;
		p.read(reinterpret_cast<unsigned char*>(&sizepaket), 4);
		if (sizepaket == 0)
		{
			dat.clear();
			return 0;
		}
		p.read(dat, sizepaket);
		return sizepaket;
	}
	bool eof()
	{
		if (!p.eof()) return false;
		else return true;
	}
};