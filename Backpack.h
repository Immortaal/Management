#pragma once
#include <time.h>
#include <iostream>
#include "Element.h"
#include <vector>
using namespace std;


class Backpack
{
private:
	float availabeBudget;
	float budgetUsed;
	float profit;
	vector<Element *> collection;

public:
	Backpack();
	Backpack(unsigned int c);
	void addElement(Element* e);
	float getAvailabeBudget() { return this->availabeBudget; }
	void displayContents();
	~Backpack();
};



