#include "stdafx.h"
#include <iostream>
#include "IPStream.h"
//#include <fstream>
#include <conio.h>
#include "Packet.h"

using namespace std;

int main()
{
	IPStream ips("1.ips");
	if (ips.is_valid()) {
		Packet packet{ ips.get() };
		cout << packet;
	}
	getch();
	return 0;
}



