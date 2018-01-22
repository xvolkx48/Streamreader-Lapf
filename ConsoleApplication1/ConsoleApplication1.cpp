#include "stdafx.h"
#include <iostream>
#include "IPStream.h"
//#include <fstream>
#include <conio.h>
#include "Packet.h"
#include "LapfPacket.h"
#include <vector>

using namespace std;

int main()
{
	IPStream ips("1.ips");
	vector<LapfPacket>testList;
	if (ips.is_valid()) {
		Packet packet{ ips.get() };
		Packet packet1{ ips.get() };
		testList=ips.getLapfPacket(packet1);
		cout << packet;
	}
	getch();
	return 0;
}



