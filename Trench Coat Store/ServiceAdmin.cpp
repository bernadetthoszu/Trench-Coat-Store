#include "ServiceAdmin.h"

ServiceAdmin::ServiceAdmin(Repo& _repo) : repo{ _repo }
{
}

void ServiceAdmin::add(const int ID, const std::string size, const std::string colour, const int price, const int quantity, const std::string photograph)
{
	Validation::validateID(ID);
	Validation::validateSize(size);
	Validation::validatePrice(price);
	Validation::validateQuantity(quantity);
	TrenchCoat coat = TrenchCoat(ID, size, colour, price, quantity, photograph);
	this->repo.add(coat);

	undoStack.push_back(std::make_unique<ActionAdd>(coat, repo));
	redoStack.clear();
}

void ServiceAdmin::remove(const int ID)
{
	TrenchCoat found = this->repo.getByID(ID);
	this->repo.remove(found);

	undoStack.push_back(std::make_unique<ActionRemove>(found, repo));
	redoStack.clear();
}

void ServiceAdmin::updateAllFields(const int ID, const std::string& new_size, const std::string& new_colour, const int new_price, const int new_quantity, const std::string& new_photograph)
{
	TrenchCoat old = this->getByID(ID); //if no exception was raised, element is in repo
	Validation::validateSize(new_size);
	Validation::validatePrice(new_price);
	Validation::validateQuantity(new_quantity);
	this->repo.updateAllFields(ID, new_size, new_colour, new_price, new_quantity, new_photograph);

	undoStack.push_back(std::make_unique<ActionUpdate>(old, repo.getByID(ID), repo));
	redoStack.clear();
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

void ServiceAdmin::undo()
{
	if (undoStack.size() == 0)
		throw UndoRedoError("No more undo's allowed!");

	std::unique_ptr<Action> a = std::move(undoStack[undoStack.size() - 1]);
	a->executeUndo();
	redoStack.push_back(std::move(a));
	undoStack.pop_back();
}

void ServiceAdmin::redo()
{
	if (redoStack.size() == 0)
		throw UndoRedoError("No more redo's allowed!");

	std::unique_ptr<Action> a = std::move(redoStack[redoStack.size() - 1]);
	a->executeRedo();
	undoStack.push_back(std::move(a));
	redoStack.pop_back();
}

void ServiceAdmin::loadRepo()
{
	this->repo.load();
}

void ServiceAdmin::storeRepo()
{
	this->repo.store();
}