#include "Basket.h"

Basket::Basket() : sum{ 0 }
{
	this->list = std::vector<TrenchCoat>();
}

void Basket::add(const TrenchCoat& e)
{
	this->list.push_back(e);
	this->sum += e.getPrice();
}

void Basket::emptyBasket()
{
	this->list.clear();
	this->sum = 0;
}

