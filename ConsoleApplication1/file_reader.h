#pragma once
#include <string>
#include <fstream>
using namespace std;


class file_reader
{
public:
	file_reader();
	file_reader(string);
	virtual ~file_reader();
	
	void open();

	int size(char*);
	char* read(int);
	int PacketSize();

	void test();
	

private:
	string path;
	int fullFiletSize;
	ifstream file;
	
};

