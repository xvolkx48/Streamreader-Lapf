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
		file.open(filename, ios::binary | ios::in);		//команда для открытия файла флаги: ios::binary - открытие в бинарном виде ios::in - открытие для чтения
		//получаем полный размер файла(с учетом первых 9 байт)
		file.seekg(0, ios::end);		//установка маркера в конец файла
		fileSize = file.tellg();		//получение позиции маркера
		file.seekg(ios::beg);			//возврат маркера в начало файла
		
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
	file.close();
}


//тестовая функция для проверки
void IPStream::test()
{
	cout << "\n"<<getPacketSize()<<endl;
	//cout << file.tellg();
	//cout << "\n"<<fullFiletSize;
}

//проверяем не закончился ли файл
bool IPStream::end()
{
	return file.eof();
}

//проверка на наличие ошибок во время работы с файловым потоком
bool IPStream::is_valid()
{
	return valid;
}

//проверяем соответствует ли заголовок файла заданному формату
void IPStream::checkHeader()
{
	char buff[9];
	if (!is_valid())
		return;
	getPacket(buff, 9);
	string file_header = string(buff, sizeof(buff));
	if (header != file_header) {
		cerr << "Bad file format\n";
		valid = false;
	}
}


//функция читает пакет из потока и возвращает объект класса Packet
Packet IPStream::get()
{
	int size = getPacketSize();		//читаем размер пакета из потока
	char buffer[65535];				//создаем массив байтов для записи данных из пакета
	getPacket(buffer, size);		//читаем пакет из потока
	return Packet{ size, buffer };	//возвращаем объект класса Packet
}