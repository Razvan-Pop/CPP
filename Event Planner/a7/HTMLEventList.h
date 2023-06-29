#pragma once
#include "FileEventList.h"

class HTMLEventList : public FileEventList{
public:
	HTMLEventList(const std::string& fileName) : FileEventList(fileName) {};
	~HTMLEventList() {};
	void writeToFile() override;
	void displayEventList() override;

};