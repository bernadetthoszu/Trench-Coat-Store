#pragma once
#include <fstream>
#include "Basket.h"
#include "Exceptions.h"

class CSVBasket : public Basket
{
private:
	std::string file_name;
public:
	CSVBasket();
	void storeBasket() override;
	void showBasket() override;
};