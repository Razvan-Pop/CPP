#pragma once
#include <string>
#include "EventList.h"

class FileEventList : public EventList {
protected:
	std::string fileName;
public:
	FileEventList(const std::string& fileName)
	{
		this->fileName = fileName;
	}
	~FileEventList() {}
	virtual void writeToFile() = 0;
	virtual void displayEventList() = 0;
};

	