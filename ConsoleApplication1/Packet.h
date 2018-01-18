#pragma once
class Packet
{
public:
	Packet(int s, char* d);
	~Packet();
private:
	int size;
	char* data;
};

