#include "stdafx.h"
#include <iostream>
#include "IPStream.h"
//#include <fstream>
#include <conio.h>

using namespace std;

int main()
{

	IPStream input_file("1.ips");
	input_file.test();

	getch();
	return 0;
}



