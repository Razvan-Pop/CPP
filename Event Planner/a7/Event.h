#pragma once
#include <string>
#include <iostream>


class DateTime 
{
private:
	int day;
	int month;
	int year;
	int hour;
	int minutes;

public:
	DateTime() : day(0), month(0), year(0), hour(0), minutes(0) {}
	DateTime(int day, int month, int year, int hour, int minutes) : day(day), month(month), year(year), hour(hour), minutes(minutes) {}

	int getDay() const { return this->day; }
	int getMonth() const { return this->month; }
	int getYear() const { return this->year; }
	int getHour() const { if (this->hour == 24) return 0;  return this->hour; }
	int getMinutes() const { return this->minutes; }

	bool operator==(const DateTime& dateTime);
	void operator=(const DateTime& dateTime);

	friend std::ostream& operator<<(std::ostream& os, const DateTime& dateTime);
};

class Event 
{
private:
	std::string title;
	std::string description;
	DateTime dateTime;
	int numberOfPeople;
	std::string link;

public:
	Event();
	Event(const std::string& title, const std::string& description, const DateTime& dateTime, int numberOfPeople, const std::string& link);

	std::string getTtile() const { return this->title; }
	std::string getDescription() const { return this->description; }
	DateTime getDateTime() const{ return this->dateTime; }
	int getNumberOfPeople() const { return this->numberOfPeople; }
	std::string getLink() const { return this->link; }

	void play();

	bool operator==(const Event& event);
	friend std::ostream& operator<<(std::ostream& os, const Event& event);
	friend std::istream& operator>>(std::istream& is, Event& event);
};