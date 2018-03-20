#include "Packet.h"
#include <vector>
#include <map>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>


vector<Packet> result;					//���������� ������ ����������� � ������ ����������
vector<Packet>::iterator result_it;		


vector < pair<unsigned char, bool>> status;	//�������� ������� ������
Packet::Packet()
{
}


Packet::~Packet()
{
}

//������� ��������� ������
void Packet::createPacketVector(unsigned char * buff, int size)
{
	unsigned char ch;						//����� ������
	vector<unsigned char> pacData;			//������ � ���������
	ch = buff[3];							//��������� ����� ������
	Packet new_pac;
	int index;
	//��������� �� ������� ������
	if ((buff[8] == 0xFF) && (buff[9] == 0x03) && (buff[10] == 0x43))
	{	
		//���� ������ ����� � ������ ��� �������� �� ������, � ���� �� ��� ������, �� ������ �� ������
		//���� �� ��� ��� ������ ��� �� ������, �� ������� ����� ���������
		for ( index = 0; index < status.size(); index++)
		{
			if (status[index].first == ch)
			{
				break;
			}
		}
		if (index == status.size())
		{
			//��������� ����� � ������ ��� ������������ �������
			status.push_back({ ch, false });
		}
		if (!status[index].second)
		{
			//�������� �����
			new_pac.chanel = ch;
			int i = 11;
			string num = "";
			while (i <= size - 2)
			{
				switch (buff[i])
				{
				case 0x2b:
					num += "+";
					break;
				case 0x30:
					num += "0";
					break;
				case 0x31:
					num += "1";
					break;
				case 0x32:
					num += "2";
					break;
				case 0x33:
					num += "3";
					break;
				case 0x34:
					num += "4";
					break;
				case 0x35:
					num += "5";
					break;
				case 0x36:
					num += "6";
					break;
				case 0x37:
					num += "7";
					break;
				case 0x38:
					num += "8";
					break;
				case 0x39:
					num += "9";
					break;
				case 0x20:
					num += " ";
					break;
				case 0x2a:
					num += "*";
					break;
				case 0x23:
					num += "#";
					break;
				default:
					break;
				}
				i++;
			}
			status[index].second = true;
			new_pac.number = num;
			new_pac.open = true;
			result.push_back(new_pac);		//���������� ����� ��������� � ������

		}
	}
	else
	{
		//��������� �� ������� �������� ������
		if ((buff[8] == 0xFF) && (buff[9] == 0x13) && (buff[10] == 0xFB))
		{
			//���� �� ������ ������ � ���� �� ������ �� ���������
			for (index = 0; index < status.size(); index++)
			{
				if (status[index].first == ch)
				{
					status[index].second = false;
					for (result_it = result.begin(); result_it != result.end(); result_it++)
					{
						if (((*result_it).chanel == ch) && ((*result_it).open))
						{
							(*result_it).open = false;
							break;
						}
					}
					break;
				}
			}
		}
		//������������� �� ������������ ����� ���� ����� �� ���������� �����
		if (buff[6] == 0x60)
		{
			int i = 8;
			while (i < size - 2)
			{
				unsigned char item = buff[i];
				pacData.push_back(item);
				i++;
			}
			for (index = 0; index < status.size(); index++)
			{
				if ((status[index].first == ch) && (status[index].second))
				{
					for (result_it = result.begin(); result_it != result.end(); result_it++)
					{
						if (((*result_it).chanel == ch) )
						{
							new_pac.chanel = (*result_it).chanel;
							new_pac.number = (*result_it).number;
							new_pac.open = true;
							if ((*result_it).open)
							{
								//��������� ������ � ����������
								(*result_it).data.insert((*result_it).data.end(), pacData.begin(), pacData.end());
								break;
							}
						}
					}
					if (result_it == result.end())
					{
						new_pac.data = pacData;
						result.push_back(new_pac);
					}
				}
			}
		}
		else
		{
			for (result_it = result.begin(); result_it != result.end(); result_it++)
			{
				if (((*result_it).chanel == ch) && (*result_it).open && ((*result_it).data.size()>0))
				{
					(*result_it).open = false;
				}
			}
		}
	}
}


//������ ����������� ������ � �����
void Packet::writeFiles()
{
	vector < pair<unsigned char, int>> channels;								//������� �������� ��� ������� ������ ���������� � 0
	//�������� ���������� ��� ����������
	for (result_it = result.begin(); result_it != result.end(); result_it++)
	{
		ostringstream filename;								//��� �����
		int count = 0;										//���������� �������� ��� �������� ������ ���������� � 0
		//���� ������ ����� ��� ���������� � ������ � �������� �� ����������� ��� �������� �� 1 � ������ ��� �������� count
		for (int i = 0; i < channels.size(); i++) {
			if (channels[i].first= (*result_it).chanel) {
				count = ++channels[i].second;
			}
		}
		//���� ������ ����� ����������� ������ ��� �� ������� ����� ������� ��� ����
		if(count==0) 
			channels.push_back({ (*result_it).chanel, 0 });

		//���������� ��� ��������� ���� � ������� � ������� ������
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		strftime(buffer, 80, "%d_%m_%y_%H_%M_%S_", &timeinfo);
		std::string cur_time = buffer;							//���������� ������� ���� � ����� � ������
		filename << cur_time;									//��������� ���� � ����� � ������ ����� �����
		filename << (*result_it).number;						//��������� ���������� ����� � ����� �����
		//�� �������� �������� ���������� ��� �����
		if (count < 10)
			filename << ".00";
		else if (count < 100)
			filename << ".0";
		filename << count;
		
		ofstream ofs( filename.str(), ios::out | ios::binary );	//������� � ��������� �� ������ � �������� ���� ����
		if (!ofs)
			throw runtime_error("Unable to open output file");	//� ������ ������ ��������
		vector<unsigned char>& data = (*result_it).data;		//��� �������� �������� ������ � ������ ������
		//���������� ������ � ���������� ������ � ����
		for (int i = 0; i < data.size(); i++)
			ofs << data[i];
		ofs.close();											//��������� ����
	}


}