#include "Exceptions.h"

ValidationError::ValidationError(std::string _message) : message{ _message } {}

const char* ValidationError::what() const noexcept
{
	//const CharT* c_str() const
	// 
	//The basic_string::c_str() is a builtin function in C++ which returns a pointer to an array that contains 
	//a null - terminated sequence of characters representing the current value of the basic_string object.This
	//array includes the same sequence of characters that make up the value of the basic_string object plus an 
	//additional terminating null - character at the end.

	return message.c_str();
}

StreamError::StreamError(std::string _message) : message{ _message } {}

const char* StreamError::what() const noexcept
{
	return message.c_str();
}

RepoError::RepoError(std::string _message) : message{ _message } {}

const char* RepoError::what() const noexcept
{
	return message.c_str();
}