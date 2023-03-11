#include "HTMLBasket.h"

HTMLBasket::HTMLBasket() : Basket()
{
	file_name = "repository.html";
}

void HTMLBasket::storeBasket()
{
	std::ofstream fout;
	fout.open("repository.html", std::ios::trunc);

	fout << "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<title>Shopping Basket</title>\n\t</head>\n\t<body>\n\t\t<table border=\"1\"\n\t\t <tr>\n\t\t\t<td>ID</td>\n\t\t\t<td>Size</td>\n\t\t\t<td>Colour</td>\n\t\t\t<td>Price</td>\n\t\t\t<td>Quantity</td>\n\t\t\t<td>Link</td>\n\t\t </tr>";

	for (auto t : list)
	{
		fout << "\n\t\t <tr>";
		fout << "\n\t\t\t<td>" << t.getID() << "</td>";
		fout << "\n\t\t\t<td>" << t.getSize() << "</td>";
		fout << "\n\t\t\t<td>" << t.getColour() << "</td>";
		fout << "\n\t\t\t<td>" << t.getPrice() << "</td>";
		fout << "\n\t\t\t<td>" << t.getQuantity() << "</td>";
		fout << "\n\t\t\t<td><a href=\"" << t.getPhotograph() << "\">Link</a></td>";
		fout << "\n\t\t </tr>";
	}

	fout << "\n\t\t</table>\n\t</body>\n</html>";

}

void HTMLBasket::showBasket()
{
	std::string command{ "start " };
	command += this->file_name;
	system(command.c_str());
}
