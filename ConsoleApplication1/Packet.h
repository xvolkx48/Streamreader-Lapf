#pragma once
#include <vector>;

using namespace std;

class Packet
{
public:
	Packet();
	unsigned char chanel;		//����� ������(3-���� ������� � 0)
	string number;				//��� �����
	vector<unsigned char> data;		//���������� ������
	bool open;					//������ ��� ������ ���� �� ���������� 8 9 10 ����� FF 13 FB
	void createPacketVector(unsigned char * buff, int size);	//������� ��������� � ���������� ������� ������
	virtual ~Packet();
	void writeFiles();
	int counter;
};

