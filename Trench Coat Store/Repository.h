#pragma once
#pragma once

#include "Trench.h"
#include "Exceptions.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>

class Repo
{
private:
	//DynamicVector stock;
	std::vector<TrenchCoat> stock;
	std::string file_name;

	void clearRepo();

public:
	Repo(const std::string& _file_name) : file_name{ _file_name } { }

	/*
	Add an element of type TrenchCoat to the repo.
	Throws RepoError if element already exists in the repo. */
	void add(const TrenchCoat& elem);

	/*
	Remove an element of type TrenchCoat from the repo.
	Throws RepoError if element is not in the repo. */
	void remove(const TrenchCoat& elem);

	/*
	Update an element's size field.
	Throws RepoError if element is not in the repo. */
	void updateSize(const int ID, const std::string& new_size);

	/*
	Update an element's colour field.
	Throws RepoError if element is not in the repo. */
	void updateColour(const int ID, const std::string& new_colour);

	/*
	Update an element's price field.
	Throws RepoError if element is not in the repo. */
	void updatePrice(const int ID, const int new_price);

	/*
	Update an element's quantity field.
	Throws RepoError if element is not in the repo. */
	void updateQuantity(const int ID, const int new_quantity);

	/*
	Update an element's photograph field.
	Throws RepoError if element is not in the repo. */
	void updatePhotograph(const int ID, const std::string& new_photograph);

	/*
	Check whether the element of type TrenchCoat is recorded in the repo.
	Returns true if so, and false otherwise. */
	bool inRepo(const TrenchCoat& elem);

	/*
	Retrieve reference to element of type TrenchCoat from the repo, having the specified ID.
	Throws RepoError if no coat with given ID was found. */
	TrenchCoat& getByID(const int ID);

	/*
	Retrieve all elements of type TrenchCoat from the repo, having the specified size.
	The list is a copy of the elements. */
	std::vector<TrenchCoat> getBySize(const std::string& size);


	std::vector<TrenchCoat> searchAll(const std::string& searchStr);

	/*
	Retrieve copy vector of all the trench coats in the repo. */
	std::vector<TrenchCoat> getAll();

	/*
	Get number of coats in the repo. */
	int length() const { return this->stock.size(); }

	/*
	Read elements of repository from file.
	Throws error if error is encountered when opening stream.*/
	void load();

	/*
	Write elements of repository to file.
	Throws error if error is encountered when opening stream.*/
	void store();
};