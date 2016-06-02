#pragma once
#include <time.h>
#include <iostream>
#include "Element.h"
#include <vector>
#include <string>
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
	string results();
	~Backpack();

	Element * elementAt(int index);
	vector<Element* > getCollection() { return collection; }
	unsigned int maxValue();
	unsigned int numberOfProducts() { return collection.size(); }
};



