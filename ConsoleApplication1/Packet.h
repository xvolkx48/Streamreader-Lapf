#pragma once
#include <iostream>

using namespace std;

class Packet
{
public:
	Packet(int s, char* d) :size{ s }, data{ d } { };
	~Packet();
	bool isLapfPacket();
	int getSize() const { return size; }
	char* getData() const { return data; }

	static const int crc_bytes = 2;
	const int lapf_header_bytes = 2;
	const int lapf_size_bytes = 1;
private:
	int size;
	char* data;

};

ostream &operator<<(ostream &os, const Packet &p);