#pragma once
#include "Repository.h"
#include "EventValidator.h"
#include "FileEventList.h"

class Controller 
{
private:
	Repository repository;
	FileEventList *eventList;
	EventValidator validator;

public:
	Controller(const Repository& r, FileEventList *p, EventValidator v) : repository{ r }, eventList(p), validator{v} {}
	Repository getRepository() const{ return this->repository; }
	FileEventList* getEventList() const { return this->eventList; }
	void addEventToEvents(const std::string& title, const std::string& description, int day, int month, int year, int hour, int minutes, int numberOfPeople, const std::string& link);
	void removeEventFromEvents(const std::string& title, int day, int month, int year, int hour, int minutes);
	void updateEvent(const std::string& title, const std::string& description, int day, int month, int year, int hour, int minutes, int numberOfPeople, const std::string& link);
	void addEventToUserEvents(int index);
	void removeEventFromUserEvents(const std::string& title, int day, int month, int year, int hour, int minutes);
	std::vector<Event> getEventsByMonth(int month) const;
	int findIndex(Event& event) const;

	void addEventToEventList(const Event& event);
	void startEventList();
	void nextEventInEventList();
	void saveEventList();
	void openEventList();
	void resetEventList();
};