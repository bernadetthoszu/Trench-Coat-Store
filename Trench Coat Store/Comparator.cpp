#include "Comparator.h"

bool ComparatorDescendingBySize::compare(const TrenchCoat e1, const TrenchCoat e2)
{
	//Check if e1 is greater than e2

	int size1, size2;
	if (e1.getSize() == "XS")
		size1 = 0;
	if (e1.getSize() == "S")
		size1 = 1;
	if (e1.getSize() == "M")
		size1 = 2;
	if (e1.getSize() == "L")
		size1 = 3;
	if (e1.getSize() == "XL")
		size1 = 4;
	if (e1.getSize() == "XXL")
		size1 = 5;

	if (e2.getSize() == "XS")
		size2 = 0;
	if (e2.getSize() == "S")
		size2 = 1;
	if (e2.getSize() == "M")
		size2 = 2;
	if (e2.getSize() == "L")
		size2 = 3;
	if (e2.getSize() == "XL")
		size2 = 4;
	if (e2.getSize() == "XXL")
		size2 = 5;

	if (size1 >= size2)
		return true;
	return false;
}

bool ComparatorAscendingByPrice::compare(const TrenchCoat p1, const TrenchCoat p2)
{
	//Check if p1 is smaller than p2

	if (p1.getPrice() <= p2.getPrice())
		return true;
	return false;
}
