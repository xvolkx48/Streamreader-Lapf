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
	
	//перевод номера канала в массив байтов
	//пока записываем файл без номера канала
	/*
	chanel_byte[0] = channel & 0xFF;
	chanel_byte[1] = (channel & 0xFF00) >> 8;
	*/
	//chanel_byte[0] = channel & 0xFF;
	//chanel_byte[1] = (channel & 0xFF00) >> 8;
	//запись номера канала в файл в бинарном виде
	
	//ofs.write(chanel_byte, 2);
	//ofs << setfill('0')<<setw(2)<< hex<< channel;
	
	//перевод размера в массив байтов
	size_byte[0] = size & 0xFF;
	size_byte[1] = (size & 0xFF00) >> 8;
	size_byte[2] = (size & 0xFF0000) >> 16;
	size_byte[3] = (size & 0xFF000000) >> 32;
	//запись размера пакета в файл в бинарном виде
	ofs.write(size_byte,4);

	//запись данных
	for (int i = 0; i != size; i++)
	{
		ofs << bufer[i];
	}
	
	//запись символов превода строки и возврата каретки 
	/*
	char b0d0a[2];
	b0d0a[0] = 0x0d;
	b0d0a[1] = 0x0a;
	ofs.write(b0d0a, 2);
	*/
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



