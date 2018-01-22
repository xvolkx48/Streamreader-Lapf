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

	int getChannel() const { return channel; }
	unsigned char getSize() const { return size; }
	char* getData() const { return data; }
private:
	int channel;
	int size;
	char* data;
};

ostream& operator<<(ostream &os, const LapfPacket &pack);
ostream& operator<<(ostream &os, const vector<LapfPacket> &packets);