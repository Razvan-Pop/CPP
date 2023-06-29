#pragma once
#include "FileEventList.h"

class CSVEventList : public FileEventList {
public:
	CSVEventList(const std::string& fileName) : FileEventList(fileName) {};
	~CSVEventList() {};
	void writeToFile() override;
	void displayEventList() override;
};