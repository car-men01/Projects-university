#pragma once
#include <exception>
#include <string>

class FileException : public std::exception
{
protected:
	std::string message;

public:
	FileException(const std::string& msg);
	virtual const char* what();
};

class RepoExceptions : public std::exception
{
protected:
	std::string message;

public:
	RepoExceptions();
	RepoExceptions(const std::string& msg);
	virtual ~RepoExceptions() {}
	virtual const char* what();
};

class DuplicateDogException : public RepoExceptions
{
	const char* what();
};

class InexistentDogException : public RepoExceptions
{
	const char* what();
};