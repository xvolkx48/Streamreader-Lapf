#pragma once
class Packet
{
public:
	Packet(int s, char* d) :size{ s }, data{ d } { };
	~Packet();
	int getSize() const { return size; }
	char* getData() const { return data; }
private:
	int size;
	char* data;
};

