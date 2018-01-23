#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include "LapfVault.h"
#include "IPStream.h"
#include<iomanip>

using namespace std;

const string output_file = "out.ips";
const string input_file = "1.ips";
const string file_header = "IP_STREAM";

void writeDataToFile(unsigned short channel, unsigned char *bufer, int size)
{
	ofstream ofs(output_file, ios::app|ios::binary);
	if (!ofs)
		throw runtime_error("Cannot open ouput file");

	//
	char chanel_byte[2], size_byte[4];
	
	//������� ������ ������ � ������ ������
	chanel_byte[0] = channel & 0xFF;
	chanel_byte[1] = (channel & 0xFF00) >> 8;
	//������ ������ ������ � ���� � �������� ����
	ofs.write(chanel_byte, 2);

	//������� ������� � ������ ������
	size_byte[0] = size & 0xFF;
	size_byte[1] = (size & 0xFF00) >> 8;
	size_byte[2] = (size & 0xFF0000) >> 16;
	size_byte[3] = (size & 0xFF000000) >> 32;
	//������ ������� ������ � ���� � �������� ����
	ofs.write(size_byte,4);

	//������ ������
	for (int i = 0; i != size; i++)
	{
		ofs << bufer[i];
	}
	ofs.close();
}
shared_ptr<LapfVault>lapfVault(new LapfVault(&writeDataToFile));



int main()
{
	
	try
	{
		IPStream ips(input_file);
		if (!ips.is_valid())
			throw runtime_error("Something wrong with ip stream");
		ofstream ofs(output_file, ios::out | ios::binary);
		ofs.write(file_header.c_str(), file_header.length());
		ofs.close();
		while (!ips.end()) {
			Packet packet{ ips.get() };
			if (packet.isLapfPacket()) {
				lapfVault->process(packet);
			}
		}

	}
	catch(runtime_error &e)
	{
		cout << e.what();
	}
	
	
	
	cout << "Press any key:";
	getch();
	return 0;
}



