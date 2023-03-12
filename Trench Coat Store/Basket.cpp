#include "Basket.h"
#include <algorithm>

void Basket::removeFromBasket(const TrenchCoat& e)
{
	std::vector<TrenchCoat>::iterator found = std::find(this->list.begin(), this->list.end(), e);
	if (found != this->list.end())
		this->list.erase(found);
}

Basket::Basket() : sum{ 0 }
{
	this->list = std::vector<TrenchCoat>();
}

void Basket::addToBasket(const TrenchCoat& e)
{
	this->list.push_back(e);
	this->sum += e.getPrice();
}

void Basket::emptyBasket()
{
	this->list.clear();
	this->sum = 0;
}

