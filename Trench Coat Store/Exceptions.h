#pragma once
#include <exception>
#include <string>

class ValidationError : public std::exception
{
private:
	std::string message;

public:
	ValidationError(std::string _message);
	const char* what() const noexcept override; //The function std::what() returns a null terminated character sequence that is used to identify the exception
};

class StreamError : public std::exception
{
private:
	std::string message;
public:
	StreamError(std::string _message);
	const char* what() const noexcept override;
};

class RepoError : public std::exception
{
private:
	std::string message;
public:
	RepoError(std::string _message);
	const char* what() const noexcept override;
};

class CommandError : public std::exception
{
private:
	std::string message;
public:
	CommandError(std::string _message) : message{ _message } {}
	const char* what() const noexcept override { return message.c_str(); }
};

class ValueError : public std::exception
{
private:
	std::string message;
public:
	ValueError(std::string _message) : message{ _message } {}
	const char* what() const noexcept override { return message.c_str(); }
};