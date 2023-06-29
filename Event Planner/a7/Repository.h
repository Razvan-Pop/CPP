#pragma once
#include <vector>
#include "Event.h"
class Repository 
{
private:
	std::vector<Event> events;
	std::vector<Event> userEvents;
	std::string filename;

public:
	Repository(const std::string& filename);
	void addEvent(Event& event);
	void removeEvent(const std::string& title, DateTime dateTime);
	void updateEvent(Event& event);
	std::vector<Event> getEvents() const { return this->events; }
	void addUserEvent(Event& event);
	void removeUserEvent(const std::string& title, DateTime dateTime);
	std::vector<Event> getUserEvents() const { return this->userEvents; }
	void generateEvents();

private:
	void readFromFile();
	void writeToFile();
};