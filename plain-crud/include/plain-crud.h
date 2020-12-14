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

	read(data);
}

template <typename DataType>
void PlainCRUD<DataType>::read(DataType& data)
{
	//cout << this->file.tellg() << endl;
	//this->file.seekg(0, ios::beg);
	//cout << this->file.tellg() << endl;
	//memset(&data, 0, sizeof(data));
	std::cout << "before read, good=" << this->file.good() << ", bad=" << this->file.bad()
		<< ", fail=" << this->file.fail() << ", eof=" << this->file.eof() << std::endl;

	this->file.read(reinterpret_cast<const char*>(&data), sizeof(data));

	std::cout << "after read, good=" << this->file.good() << ", bad=" << this->file.bad()
		<< ", fail=" << this->file.fail() << ", eof=" << this->file.eof() << std::endl;
}

template <typename DataType>
void PlainCRUD<DataType>::write(DataType& data)
{
	cout << this->file.tellp() << endl;
	this->file.seekp(0, ios::beg);
	cout << this->file.tellp() << endl;
	this->file.write(reinterpret_cast<char*>(&data), sizeof(DataType));
}

template <typename DataType>
PlainCRUD<DataType>::~PlainCRUD()
{
	file.close();
}
