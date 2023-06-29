#include "HTMLEventList.h"
#include "RepositoryExceptions.h"
#include <Windows.h>
#include <shellapi.h>
#include <fstream>

void HTMLEventList::writeToFile() {
	std::ofstream f(this->fileName, std::ios::out | std::ios::trunc);
	if (!f.is_open())
		throw FileException("No file!");

    f << "<!DOCTYPE html>" << '\n';
    f << "<html>" << '\n';
    f << "<head>" << '\n';
    f << "\t<title>Event list</title>" << '\n';
    f << "</head>" << '\n';
    f << "<body>" << '\n';
    f << "<table border = \"1\">" << '\n';
    for (auto event : this->events) {
        f << "\t<tr>" << '\n';
        f << "\t\t<td>" << event.getTtile() << "</td>" << '\n';
        f << "\t\t<td>" << event.getDescription() << "</td>" << '\n';
        f << "\t\t<td>" << event.getDateTime() << "</td>" << '\n';
        f << "\t\t<td>" << event.getNumberOfPeople() << "</td>" << '\n';
        f << "\t\t<td>" << "<a href=\"" << event.getLink() << "\">" << "Link" << "</a>" << "</td>" << '\n';
        f << "\t</tr>" << '\n';     
    }
    f << "</table>" << '\n';
    f << "</body>" << '\n';
    f << "</html>";

	f.close();
}

void HTMLEventList::displayEventList() {
    ShellExecuteA(NULL, NULL, "chrome.exe", "file:///C:/Users/Razvan/C%20C++/OOP/assignments/a7/a7/eventlist.html", NULL, SW_SHOWMAXIMIZED);
}
