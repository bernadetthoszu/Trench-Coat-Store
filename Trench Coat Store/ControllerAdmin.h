#pragma once
#include "Validation.h"
#include "Exceptions.h"
#include "Repository.h"
#include <string>

class ServiceAdmin
{
private:
	Repo& repo;

public:
	ServiceAdmin(Repo& v) : repo{ v } {}

	/*
	Add a coat with specified ID, size, colour, price, quantity, photograph to the repo.
	Preconditions: ID must be unique, size must be a value from: "XS", "S", "M", "L", "XL", "XXL", quantity and price must be positive (price also non-zero).
	Throws exception if one of these preonditions is not met or a coat with same ID already exists in repo.*/
	void add(const int ID, const std::string size, const std::string colour, const int price, const int quantity, const std::string photograph);

	/*
	Remove element with specified ID from repo.
	Throws exception is coat with specified ID is not in repo. */
	void remove(const int ID);

	/*
	Update the size of the coat with given ID.
	Throws exception if size is not one of: "XS", "S", "M", "L", "XL", "XXL", or coat with given ID is not in the repo. */
	void updateSize(const int ID, const std::string& new_size);

	/*
	Update the colour of the coat with given ID.
	Throws exception if coat with given ID is not in the repo. */
	void updateColour(const int ID, const std::string& new_colour);

	/*
	Update the price of the coat with given ID.
	Throws exception if price is not a positive, non-zero, integer or coat with given ID is not in the repo. */
	void updatePrice(const int ID, const int new_price);

	/*
	Update the gunatity of the coat with given ID.
	Throws exception if quantity is not a positive integer or coat with given ID is not in the repo.*/
	void updateQuantity(const int ID, const int new_quantity);

	/*
	Update the link to the photograph of the coat with given ID.
	Throws exception if coat with given ID is not in the repo. */
	void updatePhotograph(const int ID, const std::string& new_link);

	/*
	Get number of elemnts recorded in the repository. */
	int getRepoSize() { return this->repo.length(); }

	//DynamicVector getAllCoats() { return this->repo.getAll(); }
	/*
	Retrieve copy of the elements in the repository. */
	std::vector<TrenchCoat> getAllCoats() { return this->repo.getAll(); }


	std::vector<TrenchCoat> searchRepo(std::string searchStr) { return this->repo.searchAll(searchStr); }

	TrenchCoat getByID(int ID) { return repo.getByID(ID); }

	/*
	Read elements of repo from file.
	Throw StreamError if file could not be opened. */
	void loadRepo();

	/*
	Write elements of repo to file.
	Throw StreamError if file could not be opened. */
	void storeRepo();
};