#pragma once
#include <time.h>
#include <iostream>
#include "Element.h"
#include <vector>
using namespace std;


class Backpack
{
private:
	unsigned int max_capacity = 0;
	unsigned int curr_capacity = 0;
	unsigned int values = 0;
	vector<Element *> collection;

public:
	Backpack();
	Backpack(unsigned int capacity);
    ~Backpack();

	void addElement(Element* element);
	const unsigned int getMaxCapacity() { return max_capacity; }
	void displayContent();

	Element * elementAt(int index);
	vector<Element* > getCollection() { return collection; }
	const unsigned int maxValue();
	const unsigned int numberOfProducts() { return collection.size(); }
};



