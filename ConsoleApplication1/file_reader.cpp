#include "file_reader.h"
#include <fstream>
#include "stdafx.h"
#include <iostream>


using namespace std;

//����������� ������
file_reader::file_reader()
{
	path = "1.ips";
	open();
}

//���������� ������������
file_reader::file_reader(string fileway)
{
	path = fileway;
	open();

}

//������� �������� �����
void file_reader::open()
{
	try
	{
		file.open(path, ios::binary);
		//�������� ������ ������ �����(� ������ ������ 9 ����)
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


//������ ��������� ���������� ���� �� ������ �����
char * file_reader::read(int size)
{
	char buff[256];
	file.read((char*)&buff, size);
	return buff;
}

//������ ������ ������ (4 �����)
int file_reader::PacketSize()
{
	unsigned int result=0;
	file.read((char*)&result, 4);
	return result;
}

//���������� ������
file_reader::~file_reader()
{
}



void file_reader::test()
{
	cout << "\n"<<PacketSize()<<endl;
	//cout << file.tellg();
	//cout << "\n"<<fullFiletSize;
}