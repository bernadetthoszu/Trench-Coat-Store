#include "CSVBasket.h"

CSVBasket::CSVBasket() : Basket()
{
	file_name = "repository.csv";
}

void CSVBasket::storeBasket()
{
	std::string msg = "Error opening file!\n";
	std::ofstream fout;
	fout.open(file_name.c_str(), std::ios::trunc);
	if (!fout.is_open())
		throw StreamError(msg);

	for (auto t : list)
		fout << t.getID() << "," << t.getSize() << "," << t.getColour() << "," << t.getQuantity() << "," << t.getPrice() << "," << t.getPhotograph() << "\n";
}

void CSVBasket::showBasket()
{
	std::string command = "Notepad \"";
	command += this->file_name;
	command += "\"";
	system(command.c_str());
}
