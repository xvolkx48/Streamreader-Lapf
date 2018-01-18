#pragma once
#include <string>
#include <fstream>
#include "Packet.h"
using namespace std;


class IPStream
{
public:
	IPStream(string filename);
	~IPStream();
	void open(string filename);
	void getPacket(char* buf, int size);
	int getPacketSize();
	bool is_valid();
	Packet get();
	void test();
private:
	int fileSize;
	ifstream file;
	bool valid;
	void checkHeader();
};

