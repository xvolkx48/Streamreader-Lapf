#pragma once
#include<list>
#include<memory>
#include "LapfChannel.h"
#include "Packet.h"

using namespace std;


class LapfVault
{
public:
	LapfVault(WriteFunction w) : writeData{ w } { };
	~LapfVault();
	void process(Packet packet);
	
private:
	list<shared_ptr<LapfChannel>>channels_list;
	list<shared_ptr<LapfChannel>>::iterator channels_iterator;
	unsigned short getChannel(Packet packet);
	WriteFunction writeData;
};



