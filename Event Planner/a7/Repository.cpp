#include "Repository.h"
#include "RepositoryExceptions.h"
#include <fstream>
#include <sstream>

using namespace std;

Repository::Repository(const std::string& filename)
{
	this->filename = filename;
	this->readFromFile();
}

void Repository::addEvent(Event& event)
{
	int index;
	for (index = 0; index < this->events.size(); ++index)
		if ((this->events[index].getTtile() == event.getTtile()) && (this->events[index].getDateTime() == event.getDateTime()))
			throw DuplicateEventException();
	this->events.push_back(event);
	this->writeToFile();
}

void Repository::removeEvent(const std::string& title, DateTime dateTime)
{
	int index, idx;
	for (index = 0; index < this->events.size(); ++index)
		if ((this->events[index].getTtile() == title) && (this->events[index].getDateTime() == dateTime))
		{
			this->events.erase(this->events.begin() + index);
			for (idx = 0; idx < this->userEvents.size(); ++idx)
				if ((this->userEvents[idx].getTtile() == title) && (this->userEvents[idx].getDateTime() == dateTime))
					this->userEvents.erase(this->userEvents.begin() + idx);
			return;
		}
	if (index == this->events.size())
		throw EventNotFoundException();
	this->writeToFile();
}

void Repository::updateEvent(Event& event)
{
	int index;
	for (index = 0; index < this->events.size(); ++index)
		if ((this->events[index].getTtile() == event.getTtile()) && (event.getDateTime() == this->events[index].getDateTime()))
		{
			this->events.erase(this->events.begin() + index);
			this->events.insert(this->events.begin() + index, event);
			return;
		}
	if (index == this->events.size())
		throw EventNotFoundException();
	this->writeToFile();
}

void Repository::addUserEvent(Event& event)
{
	int index;
	for (index = 0; index < this->userEvents.size(); ++index)
		if ((this->userEvents[index].getTtile() == event.getTtile()) && (this->userEvents[index].getDateTime() == event.getDateTime()))
			throw DuplicateEventException();
	Event e{ event.getTtile(), event.getDescription(), event.getDateTime(), event.getNumberOfPeople() + 1, event.getLink() };
	for (index = 0; index < this->events.size(); ++index)
		if ((this->events[index].getTtile() == e.getTtile()) && (this->events[index].getDateTime() == e.getDateTime()))
			break;
	updateEvent(e);
	this->userEvents.push_back(e);
}

void Repository::removeUserEvent(const std::string& title, DateTime dateTime)
{
	int index;
	for (index = 0; index < this->userEvents.size(); ++index)
		if ((this->userEvents[index].getTtile() == title) && (this->userEvents[index].getDateTime() == dateTime))
		{
			Event event{ this->userEvents[index].getTtile(), this->userEvents[index].getDescription(), this->userEvents[index].getDateTime(), this->userEvents[index].getNumberOfPeople() - 1, this->userEvents[index].getLink() };
			this->userEvents.erase(this->userEvents.begin() + index);
			updateEvent(event);
			return;
		}
	if (index == this->userEvents.size())
		throw EventNotFoundException();
}

void Repository::generateEvents()
{
	DateTime dateTime4{ 10, 7, 2023, 15, 0 };
	Event event4 = Event("Startup Pitch Competition", " Calling all entrepreneurs! Pitch your startup to a panel of judges for a chance to win funding and mentorship.", dateTime4, 200, "https://www.eventbrite.com/e/startup-pitch-competition-tickets-1234567893");
	this->addEvent(event4);
	DateTime dateTime7{ 1, 10, 2023, 19, 0 };
	Event event7 = Event("Virtual Book Club Meeting", "Discuss the latest bestseller with fellow book lovers in this virtual book club meeting.", dateTime7, 20, "https://www.eventbrite.com/e/virtual-book-club-meeting-tickets-1234567896");
	this->addEvent(event7);
	DateTime dateTime8{ 31, 10, 2023, 20, 0 };
	Event event8 = Event("Halloween Costume Party", "Dress up in your best costume and join us for a night of spooky fun at this Halloween party.", dateTime8, 200, "https://www.eventbrite.com/e/halloween-costume-party-tickets-1234567897");
	this->addEvent(event8);
	DateTime dateTime5{ 14, 8, 2023, 12, 0 };
	Event event5 = Event("Live Music Festival", "Come enjoy live music from local bands and artists at this outdoor festival. Food and drinks will be available for purchase.", dateTime5, 1000, "https://www.eventbrite.com/e/live-music-festival-tickets-1234567894");
	this->addEvent(event5);
	DateTime dateTime2{ 5, 6, 2023, 9, 0 };
	Event event2 = Event("Charity Walk for Cancer Research", "Join us for a charity walk to raise funds for cancer research. All proceeds will go to the American Cancer Society.", dateTime2, 500, "https://www.eventbrite.com/e/charity-walk-for-cancer-research-tickets-1234567892");
	this->addEvent(event2);
	DateTime dateTime3{ 15, 5, 2023, 14, 0 };
	Event event3 = Event("Online Marketing Workshop", "Learn the latest online marketing techniques and strategies in this comprehensive workshop. Perfect for entrepreneurs and small business owners.", dateTime3, 100, "https://www.eventbrite.com/e/online-marketing-workshop-tickets-1234567891");
	this->addEvent(event3);
	DateTime dateTime6{ 2, 9, 2023, 18, 0 };
	Event event6 = Event("Art Exhibition Opening Reception", "Join us for the opening reception of a new art exhibition featuring works by local artists.", dateTime6, 50, "https://www.eventbrite.com/e/art-exhibition-opening-reception-tickets-1234567895");
	this->addEvent(event6);
	DateTime dateTime10{ 31, 12, 2023, 21, 0 };
	Event event10 = Event("New Year's Eve Celebration", "Ring in the new year with live music dancing and a champagne toast at this New Year's Eve celebration.", dateTime10, 500, "https://www.eventbrite.com/e/new-years-eve-celebration-tickets-1234567899");
	this->addEvent(event10);
	DateTime dateTime9{ 24, 11, 2023, 18, 0 };
	Event event9 = Event("Thanksgiving Charity Dinner", "Come together with your community for a delicious Thanksgiving dinner to benefit a local charity.", dateTime9, 100, "https://www.eventbrite.com/e/thanksgiving-charity-dinner-tickets-1234567898");
	this->addEvent(event9);
	DateTime dateTime1{ 1, 5, 2023, 10, 0 };
	Event event1 = Event("Virtual Yoga and Meditation Class", "Join us for a relaxing virtual yoga and meditation class to destress and unwind. This class is suitable for all levels.", dateTime1, 50, "https://www.eventbrite.com/e/virtual-yoga-and-meditation-class-tickets-1234567890");
	this->addEvent(event1);
}

void Repository::readFromFile()
{
	std::ifstream file(this->filename);

	if (!file.is_open())
		throw FileException("The file could not be opened!");

	Event e;
	while (file >> e)
		this->events.push_back(e);

	file.close();
}

void Repository::writeToFile()
{
	std::ofstream file(this->filename);
	if (!file.is_open())
		throw FileException("The file could not be opened!");

	for (auto e : this->events)
	{
		file << e;
	}

	file.close();
}