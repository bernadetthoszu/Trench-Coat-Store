#pragma once
#include "Validation.h"
#include "Exceptions.h"
#include "Repository.h"
#include "ActionRepo.h"
#include <string>
#include <memory>

class ServiceAdmin
{
private:
	Repo& repo;
	std::vector<std::unique_ptr<Action>> undoStack;
	std::vector<std::unique_ptr<Action>> redoStack;

public:
	ServiceAdmin(Repo& _repo);

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
	Update all fields of an element with the given new values.
	Throws RepoError if element is not in the repo. */
	void updateAllFields(const int ID, const std::string& new_size, const std::string& new_colour, const int new_price, const int new_quantity, const std::string& new_photograph);

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

	/*
	Search a given character sequence in each element of the repository. Returns a vector with all the elements containing the character sequence. */
	std::vector<TrenchCoat> searchRepo(std::string searchStr) { return this->repo.searchAll(searchStr); }

	/*
	Retrieve the coat with given ID. Raises exception if no coat with specified ID has been found. */
	TrenchCoat& getByID(int ID) { return repo.getByID(ID); }

	/*
	Undo an action. */
	void undo();

	/*
	Redo an action. */
	void redo();

	/*
	Read elements of repo from file.
	Throw StreamError if file could not be opened. */
	void loadRepo();

	/*
	Write elements of repo to file.
	Throw StreamError if file could not be opened. */
	void storeRepo();
};