#include "Ui.h"
#include <iostream>
#include "EventValidator.h"
#include "RepositoryExceptions.h"
#include <Windows.h>
#include <sstream>

#undef max // undefine the max macro defined in <windows.h>

// TODO: 
// UML Ui -> maybe delete the event list manage menu
// UML create packages and associate all the classes
// change function names and variables names
// maybe delete some of the EventList functions like next, play (if the program doesnt use them)
// maybe try to structure the code even better( make functions for reading the input readDateTime...)

using namespace std;

enum options { EXIT = 0, ADMINISTRATOR_MODE = 1, USER_MODE = 2, ADD_EVENT_DATABASE = 1, REMOVE_EVENT_DATABASE = 2, UPDATE_EVENT = 3, DISPLAY_EVENTS = 4, DISPLAY_EVENTS_BY_MONTH = 1, REMOVE_EVENT_USER = 2, DISPLAY_USER_EVENTS = 3, DISPLAY_EVENT_LIST = 4 };


void Ui::menu()
{
	cout << "[1] Administrator mode.\n";
	cout << "[2] User mode.\n";
	cout << "[0] Exit application.\n";
}

void Ui::administratorModeMenu()
{
	cout << "Administrator mode menu:\n";
	cout << "\t[1] Add event.\n";
	cout << "\t[2] Remove event.\n";
	cout << "\t[3] Update event.\n";
	cout << "\t[4] Display events.\n";
	cout << "\t[0] Exit administrator mode.\n";
}

void Ui::userModeMenu()
{
	cout << "User mode menu:\n";
	cout << "\t[1] Display events by month.\n";
	cout << "\t[2] Remove event.\n";
	cout << "\t[3] Display the selected events.\n";
	cout << "\t[4] Display the list of events.\n";
	cout << "\t[0] Exit user mode.\n";
}

void Ui::eventListManageMenu() {
	cout << "Possible commands: " << '\n';
	cout << "\t 1 - Add event." << '\n';
	cout << "\t 2 - Add events by month." << '\n';
	cout << "\t 3 - Play." << '\n';
	cout << "\t 4 - Next." << '\n';
	cout << "\t 5 - Save event list to file." << '\n';
	cout << "\t 6 - Display event list." << '\n';
	cout << "\t 0 - Back." << '\n';
}

void Ui::addEvent()
{
	cin.get();
	string title;
	cout << "The title of the event: ";
	getline(cin, title);
	string description;
	cout << "The description of the event: ";
	getline(cin, description);

	int day, month, year, hour, minutes;
	char delimiter;
	while (true) {
		cout << "The the date of the event (day/month/year): ";
		string input;
		getline(cin, input);
		stringstream ss(input);
		ss >> day >> delimiter >> month >> delimiter >> year;
		cout << "The time when the event starts (hour:minutes): ";
		getline(cin, input);
		ss.str("");
		ss.clear();
		ss << input;
		ss >> hour >> delimiter >> minutes;
		if (day < 0 || month < 0 || year < 0 || hour < 0 || minutes < 0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter only natural numbers.\n";
		}
		else
			break;
	}

	int numberOfPeople;
	while (true)
	{
		cout << "Enter the number of people attending the event: ";
		if (cin >> numberOfPeople)
			break;
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Oops! Invalid input. Please enter only natural numbers.\n";
		}
	}

	cin.get();
	string link;
	cout << "The link of the event: ";
	getline(cin, link);

	try
	{
		this->controller.addEventToEvents(title, description, day, month, year, hour, minutes, numberOfPeople, link);
		cout << "The event was added successfully!\n";
	}
	catch (EventException& exception)
	{
		for (auto error : exception.getErrors())
			cout << error;
	}
	catch (RepositoryException& exception)
	{
		cout << exception.what() << endl;
	}
}

void Ui::removeEvent()
{
	cin.get();
	string title;
	cout << "The title of the event you want to delete: ";
	getline(cin, title);

	int day, month, year, hour, minutes;
	char delimiter;
	while (true) {
		cout << "The the date of the event (day/month/year): ";
		string input;
		getline(cin, input);
		stringstream ss(input);
		ss >> day >> delimiter >> month >> delimiter >> year;
		cout << "The time when the event starts (hour:minutes): ";
		getline(cin, input);
		ss.str("");
		ss.clear();
		ss << input;
		ss >> hour >> delimiter >> minutes;
		if (day < 0 || month < 0 || year < 0 || hour < 0 || minutes < 0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter only natural numbers.\n";
		}
		else
			break;
	}

	try
	{
		this->controller.removeEventFromEvents(title, day, month, year, hour, minutes);
		cout << "The event was removed successfully\n";
	}
	catch (RepositoryException& exception)
	{
		cout << exception.what() << endl;
	}
}

void Ui::updateEvent()
{
	cin.get();
	string title;
	cout << "The title of the event you want to update: ";
	getline(cin, title);

	int day, month, year, hour, minutes;
	char delimiter;
	while (true) {
		cout << "The the date of the event (day/month/year): ";
		string input;
		getline(cin, input);
		stringstream ss(input);
		ss >> day >> delimiter >> month >> delimiter >> year;
		cout << "The time when the event starts (hour:minutes): ";
		getline(cin, input);
		ss.str("");
		ss.clear();
		ss << input;
		ss >> hour >> delimiter >> minutes;
		if (day < 0 || month < 0 || year < 0 || hour < 0 || minutes < 0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter only natural numbers.\n";
		}
		else
			break;
	}

	string description;
	cout << "The new description: ";
	getline(cin, description);

	int numberOfPeople;
	while (true)
	{
		cout << "Enter the number of people attending the event: ";
		if (cin >> numberOfPeople)
			break;
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Oops! Invalid input! Please enter a natural number.\n";
		}
	}

	cin.get();
	string link;
	cout << "Enter the new link: ";
	getline(cin, link);

	try
	{
		this->controller.updateEvent(title, description, day, month, year, hour, minutes, numberOfPeople, link);
		cout << "The event was updated successfully!\n";
	}
	catch (EventException& exception)
	{
		for (auto error : exception.getErrors())
			cout << error;
	}
	catch (RepositoryException& exception)
	{
		cout << exception.what() << endl;
	}
}

void Ui::displayEvents()
{
	vector<Event> database = this->controller.getRepository().getEvents();
	if (database.size() == 0)
	{
		cout << "There are no events.\n";
		return;
	}
	for (int index = 0; index < database.size(); ++index)
		cout << database[index] << '\n';
}

void Ui::displayEventsByMonth()
{
	string month;
	int monthInteger = 1;
	bool validInput = false;
	while (!validInput)
	{
		cout << "Enter the month: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, month);
		if (month == "")
		{
			validInput = true;
			break;
		}
		try
		{
			monthInteger = stoi(month);
			validInput = true;
		}
		catch (const invalid_argument& ia)
		{
			cerr << "Invalid month: " << ia.what() << endl;
		}
	}

	if (month == "")
	{
		vector<Event> filteredEvents = this->controller.getRepository().getEvents();
		if (filteredEvents.size() == 0)
		{
			cout << "There are no events taking place!\n";
			return;
		}
		int index, secondIndex;
		for (index = 0; index < filteredEvents.size() - 1; ++index)
			for (secondIndex = index + 1; secondIndex < filteredEvents.size(); ++secondIndex)
			{
				int firstEventYear = filteredEvents[index].getDateTime().getYear(), secondEventYear = filteredEvents[secondIndex].getDateTime().getYear(), firstEventMonth = filteredEvents[index].getDateTime().getMonth(), secondEventMonth = filteredEvents[secondIndex].getDateTime().getMonth(), firstEventDay = filteredEvents[index].getDateTime().getDay(), secondEventDay = filteredEvents[secondIndex].getDateTime().getDay(), firstEventHour = filteredEvents[index].getDateTime().getHour(), secondEventHour = filteredEvents[secondIndex].getDateTime().getHour(), firstEventMinutes = filteredEvents[index].getDateTime().getMinutes(), secondEventMinutes = filteredEvents[secondIndex].getDateTime().getMinutes();
				if ((firstEventYear > secondEventYear) || ((firstEventYear == secondEventYear) && (firstEventMonth > secondEventMonth)) || ((firstEventYear == secondEventYear) && (firstEventMonth == secondEventMonth) && (firstEventDay > secondEventDay)) || ((firstEventYear == secondEventYear) && (firstEventMonth == secondEventMonth) && (firstEventDay == secondEventDay) && (firstEventHour > secondEventHour)) || ((firstEventYear == secondEventYear) && (firstEventMonth == secondEventMonth) && (firstEventDay == secondEventDay) && (firstEventHour == secondEventHour) && (firstEventMinutes > secondEventMinutes)))
				{
					Event aux = filteredEvents[index];
					filteredEvents[index] = filteredEvents[secondIndex];
					filteredEvents[secondIndex] = aux;
				}

			}

		bool searchingForEvents = true;
		while (searchingForEvents)
		{
			for (index = 0; index < filteredEvents.size(); ++index)
			{
				ShellExecuteA(NULL, "open", filteredEvents[index].getLink().c_str(), NULL, NULL, SW_SHOWNORMAL);
				cout << filteredEvents[index] << '\n';
				cout << "Do you want to add this event to your list? [Yes/No] : ";
				string choice;
				cin >> choice;
				for (char& c : choice)
					c = tolower(c);
				if (choice == "yes")
				{
					try
					{
						int position = this->controller.findIndex(filteredEvents[index]);
						this->controller.addEventToUserEvents(position);
						cout << "The event was added successfully!\n";
					}
					catch (RepositoryException& exception)
					{
						cout << exception.what() << endl;
					}
				}
				cout << "Do you want to continue searching for events? [Yes/No] : ";
				cin >> choice;
				for (char& c : choice)
					c = tolower(c);
				if (choice == "no")
				{
					searchingForEvents = false;
					break;
				}
			}
		}
	}

	else
	{
		vector<Event> filteredEvents = this->controller.getEventsByMonth(monthInteger);
		if (filteredEvents.size() == 0)
		{
			cout << "There are no events taking place in the specified month.\n";
			return;
		}
		int index;
		bool searchingForEvents = true;
		while (searchingForEvents)
		{
			for (index = 0; index < filteredEvents.size(); ++index)
			{
				ShellExecuteA(NULL, "open", filteredEvents[index].getLink().c_str(), NULL, NULL, SW_SHOWNORMAL);
				cout << filteredEvents[index];
				cout << "Do you want to add this event to your list? [Yes/No] : ";
				string choice;
				cin >> choice;
				for (char& c : choice)
					c = tolower(c);
				if (choice == "yes")
				{
					try
					{
						int position = this->controller.findIndex(filteredEvents[index]);
						this->controller.addEventToUserEvents(position);
						cout << "The event was added successfully!\n";
					}
					catch (RepositoryException& exception)
					{
						cout << exception.what() << endl;
					}
				}
				cout << "Do you want to continue searching for events? [Yes/No] : ";
				cin >> choice;
				for (char& c : choice)
					c = tolower(c);
				if (choice == "no")
				{
					searchingForEvents = false;
					break;
				}
			}

		}
	}
}

void Ui::removeUserEvent()
{
	cin.get();
	string title;
	cout << "Enter the title of the event: ";
	getline(cin, title);

	int day, month, year, hour, minutes;
	char delimiter;
	while (true) {
		cout << "The the date of the event (day/month/year): ";
		string input;
		getline(cin, input);
		stringstream ss(input);
		ss >> day >> delimiter >> month >> delimiter >> year;
		cout << "The time when the event starts (hour:minutes): ";
		getline(cin, input);
		ss.str("");
		ss.clear();
		ss << input;
		ss >> hour >> delimiter >> minutes;
		if (day < 0 || month < 0 || year < 0 || hour < 0 || minutes < 0)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter only natural numbers.\n";
		}
		else
			break;
	}

	try
	{
		this->controller.removeEventFromUserEvents(title, day, month, year, hour, minutes);
		cout << "The event was removed successfully!\n";
	}
	catch (RepositoryException& exception)
	{
		cout << exception.what() << endl;
	}
}

void Ui::displayUserEvents()
{
	vector<Event> userEvents = this->controller.getRepository().getUserEvents();
	if (userEvents.size() == 0)
	{
		cout << "Your list is empty.\n";
		return;
	}
	int index;
	for (index = 0; index < userEvents.size(); ++index)
		cout << userEvents[index] << '\n';
}

void Ui::displayEventListFile() {
	vector<Event> list = this->controller.getRepository().getUserEvents();
	this->controller.resetEventList();
	for (auto e : list)
		this->controller.addEventToEventList(e);
	try {
		this->controller.saveEventList();
		if (this->controller.getEventList() == nullptr) {
			cout << "The event list cannot be displayed!\n";
			return;
		}
		this->controller.openEventList();
	}
	catch (FileException& exception) {
		cout << exception.what() << '\n';
	}
}

void Ui::run()
{
	int option;
	while (true)
	{
		// Menu of the application
		menu();

		// Validate input
		while (true)
		{
			cout << "Enter your option: ";
			if (cin >> option)
			{
				break;
			}
			else
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Oops! Invalid input. Please enter an integer.\n";
			}
		}

		// Exit application 
		if (option == EXIT)
			break;

		// Go throw menu
		switch (option)
		{
			// Exit main menu
			if (option == EXIT)
				break;

		case ADMINISTRATOR_MODE:
		{
			// Administrator mode menu
			administratorModeMenu();

			// Validate input
			while (true)
			{
				cout << "Enter your option: ";
				if (cin >> option)
				{
					break;
				}
				else
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Oops! Invalid input. Please enter an integer.\n";
				}
			}

			// Go throw menu
			switch (option)
			{
			case ADD_EVENT_DATABASE:
			{
				addEvent();
				break;
			}
			case REMOVE_EVENT_DATABASE:
			{
				removeEvent();
				break;
			}
			case UPDATE_EVENT:
			{
				updateEvent();
				break;
			}
			case DISPLAY_EVENTS:
			{
				displayEvents();
				break;
			}
			case EXIT:
			{
				break;
			}
			default:
			{
				printf("Oops! Invalid option.\n");
				break;
			}
			}

			// Exit administrator mode
			break;
		}

		case USER_MODE:
		{
			// User mode menu
			userModeMenu();

			// Validate input
			while (true)
			{
				cout << "Enter your option: ";
				if (cin >> option)
				{
					break;
				}
				else
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Oops! Invalid input. Please enter an integer.\n";
				}
			}

			// Go throw user mode menu
			switch (option)
			{
			case DISPLAY_EVENTS_BY_MONTH:
			{
				displayEventsByMonth();
				break;
			}
			case REMOVE_EVENT_USER:
			{
				removeUserEvent();
				break;
			}
			case DISPLAY_USER_EVENTS:
			{
				displayUserEvents();
				break;
			}
			case DISPLAY_EVENT_LIST:
			{
				displayEventListFile();
				break;
			}
			case EXIT:
			{
				break;
			}
			default:
			{
				printf("Oops! Invalid option!\n");
				break;
			}
			}

			// Exit user mode
			break;
		}

		default:
		{
			printf("Oops! Invalid option.\n");
			break;
		}
		}
	}
}