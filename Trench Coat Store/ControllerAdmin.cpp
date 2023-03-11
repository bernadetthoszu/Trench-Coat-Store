#include "ControllerAdmin.h"

void ServiceAdmin::add(const int ID, const std::string size, const std::string colour, const int price, const int quantity, const std::string photograph)
{
	Validation::validateID(ID);
	Validation::validateSize(size);
	Validation::validatePrice(price);
	Validation::validateQuantity(quantity);
	TrenchCoat coat = TrenchCoat(ID, size, colour, price, quantity, photograph);
	this->repo.add(coat);
}

void ServiceAdmin::remove(const int ID)
{
	TrenchCoat found = this->repo.getByID(ID);
	this->repo.remove(found);
}

void ServiceAdmin::updateSize(const int ID, const std::string& new_size)
{
	Validation::validateSize(new_size);
	this->repo.updateSize(ID, new_size);
}

void ServiceAdmin::updateColour(const int ID, const std::string& new_colour)
{
	this->repo.updateColour(ID, new_colour);
}

void ServiceAdmin::updatePrice(const int ID, const int new_price)
{
	Validation::validatePrice(new_price);
	this->repo.updatePrice(ID, new_price);
}

void ServiceAdmin::updateQuantity(const int ID, const int new_quantity)
{
	Validation::validateQuantity(new_quantity);
	this->repo.updateQuantity(ID, new_quantity);
}

void ServiceAdmin::updatePhotograph(const int ID, const std::string& new_link)
{
	this->repo.updatePhotograph(ID, new_link);
}

void ServiceAdmin::loadRepo()
{
	this->repo.load();
}

void ServiceAdmin::storeRepo()
{
	this->repo.store();
}