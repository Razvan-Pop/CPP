#include "Event.h"
#include <windows.h>
#include <shellapi.h>
#include <vector>
#include <sstream>
#include <iomanip>

Event::Event() {
	this->title = "N/A";
	this->description = "N/A";
	this->dateTime = DateTime(0, 0, 0, 0, 0);
	this->numberOfPeople = 0;
	this->link = "N/A";
}

Event::Event(const std::string& title, const std::string& description, const DateTime& dateTime, int numberOfPeople, const std::string& link) {
	this->title = title;
	this->description = description;
	this->dateTime = dateTime;
	this->numberOfPeople = numberOfPeople;
	this->link = link;
}

void Event::play() {
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getLink().c_str(), NULL,	SW_SHOWMAXIMIZED);
}

bool Event::operator==(const Event& event) {
	return (this->title == event.title) && (this->dateTime == event.dateTime);
}

bool DateTime::operator==(const DateTime& dateTime) {
	if ((this->day == dateTime.day) && (this->month == dateTime.month) && (this->year == dateTime.year) && (this->hour == dateTime.hour) && (this->minutes == dateTime.minutes))
		return true;
	return false;
}

void DateTime::operator=(const DateTime& dateTime) {
	this->day = dateTime.day;
	this->month = dateTime.month;
	this->year = dateTime.year;
	this->hour = dateTime.hour;
	this->minutes = dateTime.minutes;
}

std::ostream& operator<<(std::ostream& os, const DateTime& dateTime) {
	os << std::setfill('0') << std::setw(2) << dateTime.day << '/' << std::setfill('0') << std::setw(2) << dateTime.month << '/' << dateTime.year << " " << std::setfill('0') << std::setw(2) << dateTime.hour << ":" << std::setfill('0') << std::setw(2) << dateTime.minutes;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Event& event) {
	os << event.title << ", " << event.description << ", " << event.dateTime << ", " << event.numberOfPeople << ", " << event.link << '\n';
	return os;
}

std::istream& operator>>(std::istream& is, Event& event) {
	std::string line;
	getline(is, line);

	std::vector<std::string> tokens;
	std::stringstream ss(line);
	std::string token;
	while (getline(ss, token, ','))
		tokens.push_back(token);

	if (tokens.size() != 5)
		return is;

	event.title = tokens[0];
	event.description = tokens[1];
	ss.str("");
	ss.clear();
	ss << tokens[2];
	int day, month, year, hour, minutes;
	char delimiter;
	ss >> day >> delimiter >> month >> delimiter >> year >> delimiter >> hour >> delimiter >> minutes;
	event.dateTime = DateTime{ day, month, year, hour, minutes };
	event.numberOfPeople = stoi(tokens[3]);
	event.link = tokens[4];

	return is;
}  
