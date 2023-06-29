#pragma once
#include "Controller.h"

class Ui 
{
private:
	Controller controller;

public:
	Ui(const Controller& c) : controller(c) {}

	void run();

private:
	static void menu();
	static void administratorModeMenu();
	static void userModeMenu();
	static void eventListManageMenu();

	void addEvent();
	void removeEvent();
	void updateEvent();
	void displayEvents();
	void displayEventsByMonth();
	void removeUserEvent();
	void displayUserEvents();
	void displayEventListFile();
};