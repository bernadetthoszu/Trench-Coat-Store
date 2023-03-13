#include "ServiceUser.h"
#include <iostream>


void ServiceUser::newBasket(const std::string& _basket_type)
{
	if (basket != nullptr)
		delete basket;

	Validation::validateBasketType(_basket_type);

	basket_type = _basket_type;
	for (auto& c : basket_type) c = toupper(c);
	CSVBasket* b_csv = new CSVBasket;
	HTMLBasket* b_html = new HTMLBasket;

	if (basket_type == "CSV")
	{
		delete b_html;
		basket = b_csv;
	}
	else
	{
		delete b_csv;
		basket = b_html;
	}
}


void ServiceUser::addToBasket(const TrenchCoat& coat)
{
	this->basket->addToBasket(coat);
	this->basket->storeBasket();
}


std::vector<TrenchCoat> ServiceUser::seeBasket()
{
	return this->basket->getElements(); //return copy
}

ServiceUser::~ServiceUser()
{
	delete basket;
}

bool ServiceUser::search(const std::string& size)
{
	if (size == "")
	{
		search_result = this->repo.getAll();
	}
	else
	{
		Validation::validateSize(size);
		search_result = this->repo.getBySize(size);
	}

	if (search_result.size() == 0)
		return false;
	return true;
}

void ServiceUser::next()
{
	if (current == search_result.size() - 1)
		current = 0;
	else
		current++;
}

