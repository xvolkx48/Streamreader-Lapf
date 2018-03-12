#include "Packet.h"
#include <vector>
#include <map>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>


vector<Packet> result;					//записываем массив результатов в данную переменную
vector<Packet>::iterator result_it;		


Packet::Packet()
{
}


Packet::~Packet()
{
}

//функция обработки пакета
void Packet::createPacketVector(unsigned char * buff, int size)
{
	unsigned char ch;						//номер канала
	vector<unsigned char> pacData;			//данные в подпакете
	ch = buff[3];							//считываем номер канала
	//проверяем на команду записи
	if ((buff[8] == 0xFF) && (buff[9] == 0x03) && (buff[10] == 0x43))
	{	
		//ищем данный канал в списке уже открытых на запись, и если он уже открыт, то ничего не делаем
		//если он был уже закрыт или не найден, то создаем новый результат
		for (result_it = result.begin(); result_it != result.end(); result_it++)
		{
			if (((*result_it).chanel == ch)&&(open))
			{
				break;
			}
		}
		//получаем номер
		if (result_it == result.end())
		{
			Packet new_pac;
			new_pac.chanel = ch;
			int i = 11;
			string num="";
			while (i<=size-2)
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
			new_pac.number = num;
			new_pac.open = true;
			result.push_back(new_pac);		//записываем новый результат в вектор
		}
	}
	else
	{
		//проверяем на команду закрытия записи
		if ((buff[8] == 0xFF) && (buff[9] == 0x13) && (buff[10] == 0xFB))
		{
			//ищем по номеру канала и если он открыт то закрываем
			for (result_it = result.begin(); result_it != result.end(); result_it++)
			{
				if (((*result_it).chanel == ch) && (open))
				{
					(*result_it).open = false;
					break;
				}
			}
		}
		//просматриваем по контрольному флагу если стоит то записываем пакет
		if (buff[6] == 0x60)
		{
			int i = 8;
			while (i <= size - 2)
			{
				unsigned char item = buff[i];
				pacData.push_back(item);
				i++;
			}
			for (result_it = result.begin(); result_it != result.end(); result_it++)
			{
				if (((*result_it).chanel == ch) && (open))
				{
					//обновляем данные в результате
					(*result_it).data.insert((*result_it).data.end(), pacData.begin(), pacData.end());
					break;
				}
			}
		}
	}
}


//запись результатов работы в файлы
void Packet::writeFiles()
{
	vector < pair<unsigned char, int>> channels;								//счетчик векторов для каждого канала начинается с 0
	//начинаем перебирать все результаты
	for (result_it = result.begin(); result_it != result.end(); result_it++)
	{
		ostringstream filename;								//имя файла
		int count = 0;										//количество векторов для текущего канала начинается с 0
		//если данный канал уже встречался и найден в счетчике то увеличиваем его значение на 1 и отдаем это значение count
		for (int i = 0; i < channels.size(); i++) {
			if (channels[i].first= (*result_it).chanel) {
				count = ++channels[i].second;
			}
		}
		//если данный канал встречается первый раз то создаем новый счетчик для него
		if(count==0) 
			channels.push_back({ (*result_it).chanel, 0 });

		//переменные для получения даты и времени в формате строки
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		strftime(buffer, 80, "%d_%m_%y_%H_%M_%S_", &timeinfo);
		std::string cur_time = buffer;							//записываем текущее дату и время в строку
		filename << cur_time;									//добавляем дату и время в начало имени файла
		filename << (*result_it).number;						//добавляем полученный номер к имени файла
		//по счетчику получаем расширение для файла
		if (count < 10)
			filename << ".00";
		else if (count < 100)
			filename << ".0";
		filename << count;
		
		ofstream ofs( filename.str(), ios::out | ios::binary );	//создаем и открываем на запись в бинарном виде файл
		if (!ofs)
			throw runtime_error("Unable to open output file");	//в случае ошибки открытия
		vector<unsigned char>& data = (*result_it).data;		//для удобства передаем данные в другой вектор
		//перебираем вектор и записываем данные в файл
		for (int i = 0; i < data.size(); i++)
			ofs << data[i];
		ofs.close();											//закрываем файл
	}


}