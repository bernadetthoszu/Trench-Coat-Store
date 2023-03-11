#include "Validation.h"
#include <string>

void Validation::validateSize(const std::string& size)
{
	std::string msg = "Invalid size!\n";
	if (!(size == "XS" || size == "S" || size == "M" || size == "L" || size == "XL" || size == "XXL"))
		throw ValidationError(msg);
}

void Validation::validateID(const int& ID)
{
	//Price is for sure an integer at this point (invalid type error is handled in UI)
	std::string msg = "Give non-negative ID, please!\n";
	if (ID < 0)
		throw ValidationError(msg);
}

void Validation::validatePrice(const int& price)
{
	//Price is for sure an integer at this point (invalid type error is handled in UI)
	std::string msg = "Invalid numerical value for price!\n";
	if (price <= 0)
		throw ValidationError(msg);
}

void Validation::validateQuantity(const int& quantity)
{
	//Qunatity is for sure an integer at this point (invalid type error is handled in UI)
	std::string msg = "Invalid numerical value for quantity!\n";
	if (quantity <= 0)
		throw ValidationError(msg);
}

void Validation::validateBasketType(const std::string& type)
{
	std::string msg = "Invalid basket type!\n";
	if (type != "CSV" && type != "HTML" && type != "csv" && type != "html")
		throw ValidationError(msg);
}

