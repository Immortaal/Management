#pragma once
#include <time.h>
#include <iostream>
#include "Merchandise.h"
#include <vector>
using namespace std;


class Backpack
{
private:
	unsigned totalBudget;
	unsigned budgetUsed;
	float profit;
	vector<Merchandise *> collection;

public:
	Backpack();
	Backpack(unsigned int c);
	void addMerchandise(Merchandise* e);
	unsigned getTotalBudget() { return this->totalBudget; }
	void displayContents();
	~Backpack();
};



