#pragma once
#include <time.h>
#include <iostream>
#include "Element.h"
#include <vector>
using namespace std;


class Backpack
{
private:
	unsigned int max_capacity;
	unsigned int curr_capacity;
	unsigned int values;
	vector<Element *> collection;

public:
	Backpack();
	Backpack(unsigned int c);
	void addElement(Element* e);
	unsigned int get_max_capacity() { return this->max_capacity; }
	void displayContents();
	~Backpack();
};



