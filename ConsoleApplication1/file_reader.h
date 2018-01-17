#pragma once
#include <string>
using namespace std;


class file_reader
{
public:
	file_reader();
	file_reader(string);
	virtual ~file_reader();
	void test();
private:
	string path;
};

