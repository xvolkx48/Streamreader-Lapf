#pragma once
#include <string>
#include <fstream>
using namespace std;


class IPStream
{
public:
	IPStream(string filename);
	~IPStream();
	
	void open(string filename);

	char* getPacket(int);
	int getPacketSize();

	void test();
	

private:
	int fileSize;
	ifstream file;
};

