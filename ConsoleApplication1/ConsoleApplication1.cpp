#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <vector>
#include "LapfVault.h"
#include "IPStream.h"

using namespace std;

const string output_file = "out.ips";
const string input_file = "1.ips";

void writeDataToFile(unsigned short channel, unsigned char *bufer, int size)
{
	ofstream ofs(output_file, ios::app|ios::binary);
	if (!ofs)
		throw runtime_error("Cannot open ouput file");
	ofs << channel << size;
	for (int i = 0; i != size; i++)
	{
		ofs << bufer[i];
	}
}
shared_ptr<LapfVault>lapfVault(new LapfVault(&writeDataToFile));



int main()
{

	unsigned char buf[65536];


	IPStream ips(input_file);
	if (!ips.is_valid())
		throw runtime_error("Something wrong with ip stream");

	while (!ips.end()) {
		Packet packet{ ips.get() };
		if (packet.isLapfPacket()) {
			lapfVault->process(packet);
		}
	}
	getch();
	return 0;
}



