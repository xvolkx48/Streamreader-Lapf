#ifndef FILE_READER_BIN_H    // если имя ещё не определено
#define FILE_READER_BIN_H 
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
class file_reader_bin
{
	ifstream fin;
public:
	void open (string filename)
	{
		fin.open(filename, ios::binary);
	}
	unsigned read(unsigned char* data, unsigned size)
	{
		if (!fin)
		{
			cout << "\nerror" << endl;//проверка открытия файла
			return 0;
		}
		int i = 0;
		fin >> noskipws;
		for (i = 0; i < size; i++)
		{
			if (!(fin.peek() == EOF))
			{
				fin >> (data[i]);
			}
		}
		return 0;
	}
	unsigned read(vector<unsigned char>& dat, unsigned size)
	{
		if (!fin)
		{
			cout << "\nerror" << endl;//проверка открытия файла
			return 0;
		}
		int i = 0;
		for (i = 0; i<size; i++)
		{
			if (!fin.eof())
			{
				dat.push_back(fin.get());
			}
		}

		return 0;
	}
	void seekg(int step)
	{
		fin.seekg(step);
	}
	int size_file()
	{
		fin.seekg(0, std::ios::end);
		int size = fin.tellg();
		fin.seekg(0, std::ios::beg);
		return size;
	}
	bool eof()
	{
		if (!(fin)) return false;
		else return true;
			
	}
	~file_reader_bin()
	{
		fin.close();
	}
};
#endif FILE_READER_BIN_H