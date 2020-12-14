#pragma once

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <typename DataType>
class PlainCRUD {
private:
	fstream file;
	DataType data;
public:
	void load(string file_path);
	void write(DataType data);
	~PlainCRUD();
};

template <typename DataType>
void PlainCRUD<DataType>::load(string file_path)
{
	this->file.open(file_path, fstream::in | fstream::out | fstream::trunc | fstream::binary);
	if (this->file.fail()) {
		cerr << "Failed to open file";
	}

	while (!this->file.eof()) {
		this->file >> this->data;
		// fh.read((char*)&h.id, sizeof(h.id));
	};

	cout << "this->data" << endl;
}

template <typename DataType>
void PlainCRUD<DataType>::write(DataType data)
{
	this->file.write((char*)&data, sizeof(data));
}

template <typename DataType>
PlainCRUD<DataType>::~PlainCRUD()
{
	file.close();
}
