#include "EventList.h"


EventList::EventList() {
	this->current = 0;
}

void EventList::add(const Event& event) {
	this->events.push_back(event);
}

Event EventList::getCurrentEvent() {
	if (this->current == this->events.size())
		this->current = 0;
	return this->events[this->current];
	return Event{};
}

void EventList::play() {
	if (this->events.size() == 0)
		return;
	this->current = 0;
	Event currentEvent = this->getCurrentEvent();
	currentEvent.play();
}

void EventList::next() {
	if (this->events.size() == 0)
		return;
	this->current++;
	Event currentEvent = this->getCurrentEvent();
	currentEvent.play();
}

bool EventList::isEmpty() {
	return this->events.size() == 0;
}

void EventList::reset() {
	int index = 0;
	while (index < events.size()) {
		events.pop_back();
		index++;
	}
}
