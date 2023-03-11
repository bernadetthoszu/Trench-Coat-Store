#pragma once
#include <fstream>
#include "Basket.h"
#include "Exceptions.h"

class HTMLBasket : public Basket
{
private:
	std::string file_name;
public:
	HTMLBasket();
	void storeBasket() override;
	void showBasket() override;
};