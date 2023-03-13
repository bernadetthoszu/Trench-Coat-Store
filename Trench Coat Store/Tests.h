#pragma once
#include <iostream>
#include <vector>
#include "TrenchCoat.h"
#include "Repository.h"
#include "ServiceAdmin.h"
#include "ServiceUser.h"
#include "Comparator.h"

class Tests
{
public:
	friend class ValidationError;
	friend class RepoError;

	void runAllTests();
	void testDomain();
	void testRepo();
	void testController();
	void testBasket();
	void testComparator();
};