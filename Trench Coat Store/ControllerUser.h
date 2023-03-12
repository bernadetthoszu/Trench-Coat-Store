#pragma once
#include "Repository.h"
#include "Basket.h"
#include "Validation.h"
#include "CSVBasket.h"
#include "HTMLBasket.h"
#include "Comparator.h"

class ServiceUser
{
	friend class BasketWindow;
private:
	Repo& repo;
	Basket* basket;
	std::string basket_type;
	std::vector<TrenchCoat> search_result;
	int current;

public:
	ServiceUser(Repo& r) : repo{ r }, basket_type{ "" }, basket{ nullptr }, current{ 0 }, search_result{} {}

	//BASKET FUNCTIONALITIES
	/*
	Empty the contents of the current basket. */
	void newBasket(const std::string& _basket_type);

	/*
	Add a coat to the shopping basket. */
	void addToBasket(const TrenchCoat& coat);

	/*
	Retrieve basket. */
	std::vector<TrenchCoat> seeBasket();

	/*
	Shows the basket whether in Notepad (CSVBasket) or in Chrome(HTMLBasket)*/
	void showBasket() { this->basket->showBasket(); }

	/*
	Retrieve pointer to the current basket object. */
	Basket* getBasket() { return this->basket; };

	/*
	Get toatl sum to pay, consisting of elements added to the shopping basket. */
	int getSum() { return this->basket->getSum(); }

	/*
	Get number of coats added to the basket. */
	int nrCoatsInBasket() { return this->basket->nrCoats(); }


	//SEARCH RESULT FUNCTIONALITIES
	/*
	Store the basket into a CSV or HTML file.*/
	void storeBasket() { this->basket->storeBasket(); }

	/*
	Get all coats from repo with specified size.
	Throws error if specified size is not one of: "XS", "S", "M", "L", "XL", "XXL". */
	bool search(const std::string& size);

	/*
	Get the number of coats found after the search. */
	int nrFoundCoats() { return this->search_result.size(); }

	/*
	Sort the result of the search with the given sorting order (provided through the Comparator). */
	void sortSearchResult(Comparator<TrenchCoat>* c) { get_sorted(search_result, c); }

	/*
	Start parsing the search result. */
	void startParse() { current = 0; }

	/*
	Go to the next coat in the parsing process. */
	void next();

	/*
	Get the current coat, to which we got with the parsing. */
	TrenchCoat& getCurrent() { return this->search_result[current]; }

	~ServiceUser();
};
