#pragma once
#include <vector>;

using namespace std;

class Packet
{
public:
	Packet();
	unsigned char chanel;		//номер канала(3-байт начина€ с 0)
	string number;				//им€ файла
	vector<unsigned char> data;		//содержимое пакета
	bool open;					//открыт дл€ записи пока не встретитс€ 8 9 10 байты FF 13 FB
	void createPacketVector(unsigned char * buff, int size);	//функци€ обработки и накоплени€ вектора данных
	virtual ~Packet();
	void writeFiles();
	int counter;
};

