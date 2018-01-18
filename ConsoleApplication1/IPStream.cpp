#include "IPStream.h"
#include <fstream>
#include "stdafx.h"
#include <iostream>


using namespace std;

//���������� ������������
IPStream::IPStream(string filename)
{
	open(filename);
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
		
		
		file.seekg(9);
		
		cout << "\nFile open succes";
	}
	catch(...)
	{
		cout << "\nError, file not exist";
	}
}


//������ ��������� ���������� ���� �� ������ �����
char * IPStream::getPacket(int size)
{
	char buff[256];
	file.read((char*)&buff, size);
	return buff;
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