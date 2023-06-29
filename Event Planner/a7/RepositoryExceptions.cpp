#include "RepositoryExceptions.h"

RepositoryException::RepositoryException() : exception{}, message{ "" }
{
}

RepositoryException::RepositoryException(const std::string& msg) : message(msg)
{
}

const char* RepositoryException::what()
{
	return this->message.c_str();
}

const char* DuplicateEventException::what()
{
	return "There is another event with the same title and date!";
}

const char* EventNotFoundException::what()
{
	return "There is no event with the specified title and date!";
}

FileException::FileException(const std::string& msg) : message(msg)
{
}

const char* FileException::what()
{
	return this->message.c_str();
}

