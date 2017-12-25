#pragma once
#include"my.h"
#include<list>
#include<memory>
using namespace std;
//unsigned short id_n1=0 ;
//unsigned short id_n2=0 ;


typedef void(*TDataReady1)  (unsigned char *buff, int leght);
class  sort_lapf
{
public:
	sort_lapf(TDataReady1 FDdata);
	~sort_lapf();
	void SortLapf(unsigned char *buff, int size_buff);
private:
	TDataReady1 Fdata;
	list<shared_ptr<my>>id_list;
	list<shared_ptr<my>>::iterator Iter_sort;
	unsigned short id_n;
};