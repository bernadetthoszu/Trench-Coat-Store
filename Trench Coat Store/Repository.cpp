#include "Repository.h"


void Repo::clearRepo()
{
	this->stock.clear();
}

void Repo::add(const TrenchCoat& elem)
{
	std::string msg = "Trench already recorded!\n";
	int i = 0;
	if (this->inRepo(elem))
		throw RepoError(msg);
	this->stock.push_back(elem); //COPY is put into repo, not actual element
	this->store();
}


void Repo::remove(const TrenchCoat& elem)
{
	std::string msg = "Element not in repository!\n";
	bool successful_removal = false;
	std::vector<TrenchCoat>::iterator found = std::find(this->stock.begin(), this->stock.end(), elem);
	if (found != this->stock.end())
	{
		this->stock.erase(found);
		successful_removal = true;
	}
	if (!successful_removal)
		throw RepoError(msg);
	this->store();
}

void Repo::updateAllFields(const int ID, const std::string& new_size, const std::string& new_colour, const int new_price, const int new_quantity, const std::string& new_photograph)
{
	TrenchCoat& found = this->getByID(ID); //if no exception was raised, element is in repo
	found.setSize(new_size);
	found.setColour(new_colour);
	found.setPrice(new_price);
	found.setQuantity(new_quantity);
	found.setPhotograph(new_photograph);
	this->store();
}

void Repo::updateSize(const int ID, const std::string& new_size)
{
	TrenchCoat& found = this->getByID(ID); //if no exception was raised, element is in repo
	found.setSize(new_size);
	this->store();
}

void Repo::updateColour(const int ID, const std::string& new_colour)
{
	TrenchCoat& found = this->getByID(ID); //if no exception was raised, element is in repo
	found.setColour(new_colour);
	this->store();
}

void Repo::updatePrice(const int ID, const int new_price)
{
	TrenchCoat& found = this->getByID(ID); //if no exception was raised, element is in repo
	found.setPrice(new_price);
	this->store();
}

void Repo::updateQuantity(const int ID, const int new_quantity)
{
	TrenchCoat& found = this->getByID(ID); //if no exception was raised, element is in repo
	found.setQuantity(new_quantity);
	this->store();
}

void Repo::updatePhotograph(const int ID, const std::string& new_photograph)
{
	TrenchCoat& found = this->getByID(ID); //if no exception was raised, element is in repo
	found.setPhotograph(new_photograph);
	this->store();
}



bool Repo::inRepo(const TrenchCoat& elem)
{
	std::vector<TrenchCoat>::iterator found = std::find_if(this->stock.begin(), this->stock.end(), [elem](TrenchCoat& t) {return t.getID() == elem.getID(); });
	if (found != this->stock.end())
		return true;
	return false;
}



TrenchCoat& Repo::getByID(const int ID)
{
	std::string msg = "Coat not in repository!\n";
	std::vector<TrenchCoat>::iterator found = std::find_if(this->stock.begin(), this->stock.end(), [ID](TrenchCoat& t) {return t.getID() == ID; });
	if (found != this->stock.end())
		return *found;
	throw RepoError(msg);
}


std::vector<TrenchCoat> Repo::getBySize(const std::string& size)
{
	TrenchCoat t{};
	std::vector<TrenchCoat> found{};
	//!
	std::copy_if(this->stock.begin(), this->stock.end(), std::back_inserter(found), [size](TrenchCoat& t) {return size == t.getSize(); });
	return found; //copy of the search result
}

std::vector<TrenchCoat> Repo::searchAll(const std::string& searchStr)
{
	std::vector<TrenchCoat> found;
	std::copy_if(this->stock.begin(), this->stock.end(), std::back_inserter(found), [searchStr](TrenchCoat& t) { return std::to_string(t.getID()).find(searchStr.c_str()) != std::string::npos || t.getSize().find(searchStr.c_str()) != std::string::npos || t.getColour().find(searchStr.c_str()) != std::string::npos || std::to_string(t.getQuantity()).find(searchStr.c_str()) != std::string::npos || std::to_string(t.getPrice()).find(searchStr.c_str()) != std::string::npos || t.getPhotograph().find(searchStr.c_str()) != std::string::npos; });
	return found;
}

std::vector<TrenchCoat> Repo::getAll()
{
	return this->stock; //copy of repo
}


void Repo::load()
{
	std::ifstream fin(this->file_name.c_str());
	if (!fin.good())
		throw StreamError("Error opening file!\n");

	this->clearRepo();

	TrenchCoat coat;
	while (fin >> coat)
		this->add(coat);

	fin.close();
}

void Repo::store()
{
	std::ofstream fout(this->file_name.c_str());
	if (!fout.is_open())
		throw StreamError("Error opening file!\n");

	for (TrenchCoat coat : this->stock)
		fout << coat;

	fout.close();
}