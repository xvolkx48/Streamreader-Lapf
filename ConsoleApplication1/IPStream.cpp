#include "IPStream.h"
#include <fstream>
#include "stdafx.h"
#include <iostream>
#include <vector>


using namespace std;

//конструктор
IPStream::IPStream(string filename)
{
	valid = true;
	open(filename);
	checkHeader();
}

//попытка открытия файла
void IPStream::open(string filename)
{
	try
	{
		file.open(filename, ios::binary);
		//получаем полный размер файла(с учетом первых 9 байт)
		file.seekg(0, ios::end);
		fileSize = file.tellg();
		file.seekg(ios::beg);
		
		cout << "File open succes\n";
	}
	catch(...)
	{
		cout << "Error, file not exist\n";
		valid = false;
	}
}


//читаем указанное количество байт из потока файла
void IPStream::getPacket(char* buff, int size)
{	
	file.read(buff, size);
}

//читаем размер пакета (4 байта)
int IPStream::getPacketSize()
{
	unsigned int result=0;
	file.read((char*)&result, 4);
	return result;
}

//деструктор класса
IPStream::~IPStream()
{
}



void IPStream::test()
{
	cout << "\n"<<getPacketSize()<<endl;
	//cout << file.tellg();
	//cout << "\n"<<fullFiletSize;
}

bool IPStream::is_valid()
{
	return valid;
}

void IPStream::checkHeader()
{
	char buff[9];
	if (!is_valid())
		return;
	string header = "IP_STREAM";
	getPacket(buff, 9);
	string file_header = string(buff, sizeof(buff));

	if (header != file_header) {
		cerr << "Bad file format\n";
		valid = false;
	}
}

Packet IPStream::get()
{
	int size = getPacketSize();
	char buffer[65535];
	getPacket(buffer, size);
	return Packet{ size, buffer };
}

vector<LapfPacket> IPStream::getLapfPacket(Packet pack)
{
	vector<LapfPacket> result = {};
	char* data = pack.getData();
	char smallPack[256];
	int chanel =(data[0] & 0xFC) | ((data[1] & 0xF0) >> 4) ;
	unsigned char size;
	//берем с третьего байта, т.к. первые 2 это номер канала а 3-ий размер пакета
	int position = 2;
	if (pack.isLapfPacket())
	{
		while (((pack.getSize()-2)-position)>0)
		{
			size = data[position];
			position++;
			for (int i = position; i <= position+size; i++)
			{
				smallPack[i - position] = data[i];
			}
			position += size;
			result.push_back(LapfPacket(chanel,size,smallPack));
		}
	}
	else
	{
		
	}
	return result;
}