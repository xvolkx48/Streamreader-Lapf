#include "IPStream.h"
#include <fstream>
#include "stdafx.h"
#include <iostream>


using namespace std;

//перегрузка конструктора
IPStream::IPStream(string filename)
{
	open(filename);
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
		
		
		file.seekg(9);
		
		cout << "\nFile open succes";
	}
	catch(...)
	{
		cout << "\nError, file not exist";
	}
}


//читаем указанное количество байт из потока файла
char * IPStream::getPacket(int size)
{
	char buff[256];
	file.read((char*)&buff, size);
	return buff;
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