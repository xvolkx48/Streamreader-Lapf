///#include "targetver.h"
#pragma once
typedef void(*TDataReady1)  (unsigned char *buff, int leght);
class my 
{
public:
	my(TDataReady1 FDdata);
	~my();
	short id_class;
	void work(unsigned char *buff, int size_buff);//����� ���� ������?
private:
	TDataReady1 Fdata;
};