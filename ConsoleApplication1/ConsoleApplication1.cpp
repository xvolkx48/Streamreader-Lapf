#include "stdafx.h"
#include <iostream>
#include "file_reader.h"
//#include <fstream>
#include <conio.h>

using namespace std;

int main()
{
	char* buf;
	int size;
	file_reader input_file("1.ips");
	input_file.test();
	getch();
	return 0;
}



