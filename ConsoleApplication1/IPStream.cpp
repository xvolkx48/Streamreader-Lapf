#include "IPStream.h"
#include <fstream>
#include "stdafx.h"
#include <iostream>


using namespace std;

//�����������
IPStream::IPStream(string filename)
{
	valid = true;
	open(filename);
	checkHeader();
}

//������� �������� �����
void IPStream::open(string filename)
{
	try
	{
		file.open(filename, ios::binary);
		//�������� ������ ������ �����(� ������ ������ 9 ����)
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


//������ ��������� ���������� ���� �� ������ �����
void IPStream::getPacket(char* buff, int size)
{	
	file.read(buff, size);
}

//������ ������ ������ (4 �����)
int IPStream::getPacketSize()
{
	unsigned int result=0;
	file.read((char*)&result, 4);
	return result;
}

//���������� ������
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