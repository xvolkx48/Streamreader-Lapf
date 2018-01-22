#pragma once
#include <iostream>
#include <vector>

using namespace std;
class LapfPacket
{
public:
	LapfPacket(int c, unsigned char s, char* d)
		:channel{ c }, size{ s }, data{ d }
	{ };
	~LapfPacket();

	int getChannel() { return channel; }
	unsigned char getSize() { return size; }
	char* getData() { return data; }
private:
	int channel;
	int size;
	char* data;
};

ostream& operator<<(ostream& os, LapfPacket pack);
ostream& operator<<(ostream& os, vector<LapfPacket> packets);