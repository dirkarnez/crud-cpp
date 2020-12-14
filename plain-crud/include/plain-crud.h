#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename DataType>
class PlainCRUD {
private:
	fstream file;
public:
	void load(string file_path, DataType& data);
	void read(DataType& data);
	void write(DataType& data);
	~PlainCRUD();
};

template <typename DataType>
void PlainCRUD<DataType>::load(string file_path, DataType& data)
{
	this->file.open(file_path, fstream::in | fstream::out | fstream::binary);
	if (this->file.fail()) {
		this->file.open(file_path, fstream::out | fstream::binary);
		this->file.close();
		this->file.open(file_path, fstream::in | fstream::out | fstream::binary);
	}
	else {
		this->read(data);
	}
}

template <typename DataType>
void PlainCRUD<DataType>::read(DataType& data)
{
	this->file.read(reinterpret_cast<char*>(&data), sizeof(data));
}

template <typename DataType>
void PlainCRUD<DataType>::write(DataType& data)
{
	this->file.seekp(0, ios::beg);
	this->file.write(reinterpret_cast<char*>(&data), sizeof(DataType));
}

template <typename DataType>
PlainCRUD<DataType>::~PlainCRUD()
{
	file.close();
}
