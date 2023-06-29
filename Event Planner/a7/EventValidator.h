#pragma once
#include "Event.h"
#include <vector>

class EventException 
{
private:
	std::vector<std::string> errors;

public:
	EventException(std::vector<std::string> _errors);
	std::vector<std::string> getErrors() const;
};

class EventValidator 
{
public:
	EventValidator() {};
	void validate(const Event& event);
};	