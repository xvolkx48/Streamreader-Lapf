#include "file_reader.h"
#include <fstream>
#include "stdafx.h"
#include <iostream>


using namespace std;

//конструктор класса
file_reader::file_reader()
{
	path = "1.ips";
	open();
}

//перегрузка конструктора
file_reader::file_reader(string fileway)
{
	path = fileway;
	open();

}

//попытка открытия файла
void file_reader::open()
{
	try
	{
		file.open(path, ios::binary);
		//получаем полный размер файла(с учетом первых 9 байт)
		file.seekg(0, ios::end);
		fullFiletSize = file.tellg();
		
		
		file.seekg(9);
		
		cout << "\nFile open succes";
	}
	catch(...)
	{
		cout << "\nError, file not exist";
	}
}


//читаем указанное количество байт из потока файла
char * file_reader::read(int size)
{
	char buff[256];
	file.read((char*)&buff, size);
	return buff;
}

//читаем размер пакета (4 байта)
int file_reader::PacketSize()
{
	unsigned int result=0;
	file.read((char*)&result, 4);
	return result;
}

//деструктор класса
file_reader::~file_reader()
{
}



void file_reader::test()
{
	cout << "\n"<<PacketSize()<<endl;
	//cout << file.tellg();
	//cout << "\n"<<fullFiletSize;
}