#include "Tests.h"
#include "assert.h"
#include <iostream>

void Tests::runAllTests()
{
	testDomain();
	testRepo();
	testController();
	testBasket();
	testComparator();
	std::cout << "All tests passed successfully!\n";
}

void Tests::testDomain()
{
	TrenchCoat coat1 = TrenchCoat(1, "S", "blue", 120, 200, "asdf");
	TrenchCoat coat2 = coat1;
	assert(coat2.getID() == coat1.getID());
	assert(coat2.getSize() == "S");
	assert(coat2.getColour() == "blue");
	assert(coat2.getPrice() == 120);
	assert(coat2.getQuantity() == 200);
	assert(coat2.getPhotograph() == "asdf");
	assert(coat2.getID() == coat1.getID());
	assert(coat2.getID() == coat1.getID());
	assert(coat2 == coat1);
	TrenchCoat coat3 = TrenchCoat();
	coat3 = coat2;
	assert(coat3 == coat2);
	assert(coat3 == coat1);
	assert(coat1.toSring() == "ID: 1, Size: S, Colour: blue, Quantity: 200, Price: 120,\n Photograph: asdf");
	coat1.setPrice(170);
	coat1.setQuantity(50);
	assert(!(coat1 == coat2));
	coat1.setSize("M");
	assert(coat1.getSize() == "M");
	coat1.setColour("yellow");
	assert(coat1.getColour() == "yellow");
	coat1.setPhotograph("asdf");
	assert(coat1.getPhotograph() == "asdf");

	std::cout << "Domain tests done!\n";
}


void Tests::testRepo()
{
	Repo repo = Repo("repository_test.txt");
	assert(repo.length() == 0);
	TrenchCoat coat1 = TrenchCoat(1, "S", "blue", 120, 200, "asdf");
	TrenchCoat coat2 = coat1;
	TrenchCoat coat3 = TrenchCoat();

	//test add
	repo.add(coat1);
	assert(repo.length() == 1);
	try {
		repo.add(coat2);
	}
	catch (RepoError& re)
	{
		std::string msg = "Trench already recorded!\n";
		std::string what{ re.what() };
		assert(what == msg);
	}
	repo.add(coat3);
	assert(repo.length() == 2);

	//test remove
	repo.remove(coat3);
	assert(repo.length() == 1);
	try {
		repo.remove(coat3);
	}
	catch (RepoError& re)
	{
		std::string msg = "Element not in repository!\n";
		std::string what{ re.what() };
		assert(what == msg);
	}
	assert(repo.length() == 1);

	//test updating an element
	repo.updatePrice(1, 150);
	repo.updateQuantity(1, 100);
	repo.updateSize(1, "M");
	repo.updateColour(1, "yellow");
	repo.updatePhotograph(1, "asdf");
	assert(repo.getByID(coat1.getID()).getPrice() == 150);
	assert(repo.getByID(coat1.getID()).getQuantity() == 100);
	assert(repo.getByID(coat1.getID()).getSize() == "M");
	assert(repo.getByID(coat1.getID()).getColour() == "yellow");
	assert(repo.getByID(coat1.getID()).getPhotograph() == "asdf");
	try {
		repo.updatePrice(0, 100);
	}
	catch (RepoError& re)
	{
		std::string msg = "Coat not in repository!\n";
		std::string what{ re.what() };
		assert(what == msg);
	}

	std::vector<TrenchCoat> all_stock = repo.getAll();
	assert(all_stock.size() == repo.length());
	all_stock[0].setPrice(1000);
	assert(repo.getByID(1).getPrice() == 150);
	assert(all_stock[0].getPrice() == 1000);

	std::vector<TrenchCoat> search_result = repo.getBySize("M");
	assert(search_result.size() == 1);
	assert(search_result[0].getID() == 1);
	search_result = repo.getBySize("S");
	assert(search_result.size() == 0);

	TrenchCoat t2{ 2, "M", "mustard", 200, 100, "asdf1" };
	TrenchCoat t3{ 3, "S", "marine", 1000, 100, "asdf2" };
	repo.add(t2);
	repo.add(t3);

	std::cout << "Repo tests done!\n";
}

void Tests::testController()
{
	Repo repo = Repo("repository_test.txt");
	CSVBasket basket = CSVBasket();
	ServiceAdmin srv_a = ServiceAdmin(repo);
	ServiceUser srv_u = ServiceUser(repo);
	srv_u.newBasket("CSV");

	//TEST SERVICE ADMIN

	assert(srv_a.getRepoSize() == 0);

	srv_a.add(1, "S", "blue", 300, 100, "asdf");
	srv_a.add(2, "M", "mustard", 200, 100, "asdf1");
	srv_a.add(3, "S", "marine", 1000, 100, "asdf2");
	assert(srv_a.getRepoSize() == 3);
	assert(srv_a.getAllCoats()[0].getPhotograph() == "asdf");
	srv_a.add(4, "M", "blue", 300, 100, "asdf");
	assert(srv_a.getRepoSize() == 4);
	try {
		srv_a.add(-1, "M", "mustard", 200, 100, "asdf1");
	}
	catch (ValidationError& ve)
	{
		std::string msg = "Give non-negative ID, please!\n";
		std::string what{ ve.what() };
		assert(what == msg);
	}
	try {
		srv_a.add(1, "M", "mustard", 200, 100, "asdf1");
	}
	catch (RepoError& re)
	{
		std::string msg = "Trench already recorded!\n";
		std::string what{ re.what() };
		assert(what == msg);
	}
	try {
		srv_a.add(5, "XXS", "mustard", 200, 100, "asdf1");
	}
	catch (ValidationError& ve)
	{
		std::string msg = "Invalid size!\n";
		std::string what{ ve.what() };
		assert(what == msg);
	}
	try {
		srv_a.add(5, "XS", "mustard", -10, 100, "asdf1");
	}
	catch (ValidationError& ve)
	{
		std::string msg = "Invalid numerical value for price!\n";
		std::string what{ ve.what() };
		assert(what == msg);
	}
	try {
		srv_a.add(5, "XS", "mustard", 200, -10, "asdf1");
	}
	catch (ValidationError& ve)
	{
		std::string msg = "Invalid numerical value for quantity!\n";
		std::string what{ ve.what() };
		assert(what == msg);
	}

	srv_a.remove(1);
	assert(srv_a.getRepoSize() == 3);
	try {
		srv_a.remove(1);
	}
	catch (RepoError& re)
	{
		std::string msg = "Coat not in repository!\n";
		std::string what{ re.what() };
		assert(what == msg);
	}

	srv_a.updatePrice(3, 500);
	srv_a.updateQuantity(3, 20);
	srv_a.updateSize(3, "M");
	srv_a.updateColour(3, "yellow");
	srv_a.updatePhotograph(3, "aaaaa");
	std::vector<TrenchCoat> all_coats = srv_a.getAllCoats();
	assert(all_coats[2].getID() == 4);
	assert(all_coats[2].getPrice() == 300);
	assert(all_coats[2].getQuantity() == 100);

	std::cout << "ServiceAdmin tests done!\n";

	//TEST SERVICE USER
	srv_u.search("S");
	int found = srv_u.nrFoundCoats();
	assert(found == 0);
	srv_u.search("M");
	found = srv_u.nrFoundCoats();
	assert(found == 3);
	srv_u.search("");
	found = srv_u.nrFoundCoats();
	assert(found == 3);

	srv_u.startParse();
	srv_u.next();
	TrenchCoat t = srv_u.getCurrent();
	assert(t.getID() == 3);
	srv_u.next();
	srv_u.next();
	t = srv_u.getCurrent();
	assert(t.getID() == 2);

	std::cout << "ServiceUser tests done!\n";
}

void Tests::testBasket()
{
	CSVBasket b{};
	TrenchCoat t1{ 1, "S", "blue", 120, 200, "asdf" };
	TrenchCoat t2{ 2, "M", "mustard", 200, 100, "asdf1" };
	TrenchCoat t3{ 3, "S", "marine", 1000, 100, "asdf2" };

	assert(b.getSum() == 0);
	b.add(t1);
	b.add(t2);
	assert(b.getSum() == 320);
	assert(b[1].getID() == 2);
	b.emptyBasket();
	assert(b.getSum() == 0);

	std::cout << "Basket tests done!\n";
}

void Tests::testComparator()
{
	TrenchCoat t1{ 1, "S", "blue", 120, 100, "asdf" };
	TrenchCoat t2{ 2, "M", "mustard", 200, 200, "asdf1" };
	TrenchCoat t3{ 3, "S", "marine", 1000, 1000, "asdf2" };

	std::vector<TrenchCoat> v;
	v.push_back(t1);
	v.push_back(t2);
	v.push_back(t3);

	ComparatorAscendingByPrice* cp = new ComparatorAscendingByPrice; // 3 2 1
	ComparatorDescendingBySize* cs = new ComparatorDescendingBySize; // 2 1 3

	assert(cp->compare(t1, t2) == true);
	assert(cs->compare(t1, t2) == false);

	get_sorted(v, cp);
	assert(v[0].getID() == 1);
	assert(v[1].getID() == 2);
	assert(v[2].getID() == 3);

	get_sorted(v, cs);
	assert(v[0].getID() == 2);
	assert(v[1].getID() == 1);
	assert(v[2].getID() == 3);

	delete cp;
	delete cs;

	std::cout << "Comparator tests done!\n";
}
