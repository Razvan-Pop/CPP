#pragma once
#include <vector>
#include "Event.h"

class EventList
{
protected:
	std::vector<Event> events;
	int current;

public:
	EventList();

	// Adds a event to the eventList.
	void add(const Event& event);

	// Returns the event that is currently opened.
	Event getCurrentEvent();

	// Starts the eventList - opens the first event.
	void play();

	// Opens the next event in the eventList.
	void next();

	// Checks if the eventList is empty.
	bool isEmpty();

	// Resets the eventlist size.
	void reset();

	virtual ~EventList() {}
};

