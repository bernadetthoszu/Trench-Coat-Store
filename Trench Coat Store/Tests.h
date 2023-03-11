#pragma once
#include <iostream>
#include <vector>
#include "Trench.h"
#include "Repository.h"
#include "ControllerAdmin.h"
#include "ControllerUser.h"
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