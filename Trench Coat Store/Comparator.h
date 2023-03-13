#pragma once
#include "TrenchCoat.h"
#include <string>
#include <algorithm>

template <typename T>
class Comparator
{
public:
	virtual bool compare(const T e1, const T e2) = 0;
};

class ComparatorDescendingBySize : public Comparator<TrenchCoat>
{
public:
	bool compare(const TrenchCoat t1, const TrenchCoat t2) override;
};

class ComparatorAscendingByPrice : public Comparator<TrenchCoat>
{
public:
	bool compare(const TrenchCoat t1, const TrenchCoat t2) override;
};

template <typename T>
void get_sorted(std::vector<T>& v, Comparator<T>* c)
{
	int i, j;
	T aux{};
	for (i = 0; i < v.size() - 1; i++)
	{
		for (j = i + 1; j < v.size(); j++)
		{
			if (!c->compare(v[i], v[j]))
			{
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}