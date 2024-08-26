#include "RepoExceptions.h"

FileException::FileException(const std::string& msg) : message(msg)
{
}

const char* FileException::what()
{
	return message.c_str();
}

RepoExceptions::RepoExceptions() : exception{}, message{ "" }
{
}

RepoExceptions::RepoExceptions(const std::string& msg) : message{ msg }
{
}

const char* RepoExceptions::what()
{
	return this->message.c_str();
}

const char* DuplicateDogException::what()
{
	return "There is another dog with the same breed and name!";
}

const char* InexistentDogException::what()
{
	return "There is no dog with the given breed and name!";
}