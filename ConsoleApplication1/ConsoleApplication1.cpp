#include "stdafx.h"
#include <iostream>
#include "IPStream.h"
#include <conio.h>
#include "Packet.h"
#include "LapfPacket.h"
#include <vector>

using namespace std;

int main()
{
	IPStream ips("1.ips");
	if (!ips.is_valid())
		throw runtime_error("Something wrong with ip stream");
	while (!ips.end()) {
		Packet packet = ips.get();
		vector<LapfPacket>testList;
		cout <<"Packet: \n"<< packet<<"\n";
		if (packet.isLapfPacket()) {
			packet.getLapfPacket(testList);
			cout << testList;
		}
	}
	getch();
	return 0;
}



