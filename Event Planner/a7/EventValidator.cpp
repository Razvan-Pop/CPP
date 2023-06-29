#include "EventValidator.h"

using namespace std;

EventException::EventException(vector<string> _errors) : errors{ _errors } {}

vector<string> EventException::getErrors() const {
	return this->errors;
}

void EventValidator::validate(const Event& event) {
	vector<string> errors;
	int day = event.getDateTime().getDay();
	int month = event.getDateTime().getMonth();
	int year = event.getDateTime().getYear();
	int hour = event.getDateTime().getHour();
	int minutes = event.getDateTime().getMinutes();

	if (event.getTtile().size() < 3)
		errors.push_back("The title name cannot be less than 2 characters!\n");

	if ((day <= 0 || month <= 0 || year <= 0) || (month > 12 || day > 31 || year < 2023) || (month == 2 && (year % 400 != 0 && year % 100 != 0 && year % 4 != 0) && day > 28) || (month == 2 && (year % 400 == 0 || year % 100 == 0 || year % 4 == 0) && day > 29) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
		errors.push_back("The date of the event is not valid!\n");
	if (hour < 0 || minutes < 0 || minutes >= 60 || hour > 24)
		errors.push_back("The time of the event is not valid!\n");

	if (event.getNumberOfPeople() < 0)
		errors.push_back("The number of people attending the event cannot be negative!\n");

	size_t posWWW = event.getLink().find("www");
	size_t posHTTPS = event.getLink().find("https");
	if (posWWW != 0 && posHTTPS != 0)
		errors.push_back("The link must start with one of the following strings: \"www\" or \"https\"\n");

	if (errors.size() > 0)
		throw EventException(errors);
}