#pragma once

using namespace std;
class LapfPacket
{
public:
	LapfPacket(int, unsigned char, char*);
	virtual ~LapfPacket();
private:
	int chanel;
	unsigned char size;
	char* data;
};

