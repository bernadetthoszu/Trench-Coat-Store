#pragma once
#include "Trench.h"
#include <vector>
class Basket
{
protected:

	std::vector<TrenchCoat> list;
	int sum;
	//int currentCoat;

public:
	Basket();

	/*
	Get total sum to pay for the elemnts in the shopping basket. */
	int getSum() const { return this->sum; }

	/*
	Add a coat to the shopping basket. */
	void add(const TrenchCoat& e);

	/*
	Remove everything added to the basket (empty the basket). Sum will be 0. */
	void emptyBasket();

	std::vector<TrenchCoat> getElements() { return this->list; }

	/*
	Get the number of coats added to the basket. */
	int nrCoats() { return this->list.size(); }

	virtual void storeBasket() = 0;
	virtual void showBasket() = 0;


	TrenchCoat& operator[](int index) { return this->list[index]; }

};
