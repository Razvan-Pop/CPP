#include "Controller.h"
#include <algorithm>

void Controller::addEventToEvents(const std::string& title, const std::string& description, int day, int month, int year, int hour, int minutes, int numberOfPeople, const std::string& link) 
{
	Event event{ title, description, DateTime{day, month, year, hour, minutes}, numberOfPeople, link};
	this->validator.validate(event);
	this->repository.addEvent(event);
}

void Controller::removeEventFromEvents(const std::string& title, int day, int month, int year, int hour, int minutes) 
{
	DateTime dateTime{ day, month, year, hour, minutes };
	this->repository.removeEvent(title, dateTime);
}

void Controller::updateEvent(const std::string& title, const std::string& description, int day, int month, int year, int hour, int minutes, int numberOfPeople, const std::string& link)
{
	Event event{ title, description, DateTime{day, month, year, hour, minutes}, numberOfPeople, link };
	this->validator.validate(event);
	this->repository.updateEvent(event);
}

void Controller::addEventToUserEvents(int index)
{
	if (index >= 0 && index < this->repository.getEvents().size()) 
	{
		Event event{ this->repository.getEvents()[index] };
		this->repository.addUserEvent(event);
	}
		
}

void Controller::removeEventFromUserEvents(const std::string& title, int day, int month, int year, int hour, int minutes)
{
	this->repository.removeUserEvent(title, DateTime{ day, month, year, hour, minutes });
}

std::vector<Event> Controller::getEventsByMonth(int month) const
{
	std::vector<Event> filteredEvents;
	const auto& events = this->repository.getEvents();
	std::copy_if(events.begin(), events.end(), std::back_inserter(filteredEvents), [=](Event event) {
		return event.getDateTime().getMonth() == month;
	});
	return filteredEvents;
}

int Controller::findIndex(Event& event) const
{
	std::vector<Event> events = this->repository.getEvents();
	int index;
	for (index = 0; index < events.size(); ++index)
		if ((events[index].getTtile() == event.getTtile()) && (events[index].getDateTime() == event.getDateTime()))
			return index;
	return 0;
}

void Controller::addEventToEventList(const Event& event) {
	if (this->eventList == nullptr)
		return;
	this->eventList->add(event);
}

void Controller::startEventList() {
	if (this->eventList == nullptr)
		return;
	this->eventList->play();
}

void Controller::nextEventInEventList() {
	if (this->eventList == nullptr)
		return;
	this->eventList->next();
}

void Controller::saveEventList() {
	if (this->eventList == nullptr)
		return;
	this->eventList->writeToFile();
}

void Controller::openEventList() {
	if (this->eventList == nullptr)
		return;
	this->eventList->displayEventList();
}

void Controller::resetEventList() {
	this->eventList->reset();
}
