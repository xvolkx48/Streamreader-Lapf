#pragma once
#include "Packet.h";
#include <iostream>;

using namespace std;

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

ostream &operator<<(ostream &os, const Packet &p);