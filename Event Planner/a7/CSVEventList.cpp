#include "CSVEventList.h"
#include <Windows.h>
#include <fstream>
#include "RepositoryExceptions.h"

void CSVEventList::writeToFile() {
	std::ofstream f(this->fileName, std::ios::out | std::ios::trunc);
	if (!f.is_open())
		throw FileException("File couldn't be opened!");
	for (auto e : this->events)
		f << e;
	f.close();
}

void CSVEventList::displayEventList() {
	ShellExecuteA(NULL, NULL, "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", this->fileName.c_str(), NULL, SW_SHOWMAXIMIZED);
}
