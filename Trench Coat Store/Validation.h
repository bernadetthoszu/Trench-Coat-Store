#pragma once
#include "ControllerAdmin.h"
#include "ControllerUser.h"
#include "Exceptions.h"
#include <string>

class Validation
{
public:
	/*
	Validate the inout size. Size is valid if it is one of: "XS", "S", "M", "L", "XL", "XXL".
	Throws ValidationError if data checked is invalid. */
	static void validateSize(const std::string& size);

	/*
	Validate the input ID for a coat. ID must be a positive numerical value.
	Throws ValidationError if data checked is invalid. */
	static void validateID(const int& ID);

	/*
	Validate the input price. Price must be a positive, non-zero, numerical value.
	Throws ValidationError if data checked is invalid. */
	static void validatePrice(const int& price);

	/*
	Validate the input quantity. Quantity must be a positive, non-zero, numerical value.
	Throws ValidationError if data checked is invalid. */
	static void validateQuantity(const int& quantity);

	static void validateBasketType(const std::string& type);
};