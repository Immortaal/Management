#include "stdafx.h"
#include "Backpack.h"


Backpack::Backpack()
{
	this->availabeBudget = 0;
	this->budgetUsed = 0;
	this->profit = 0;
	this->collection = vector<Element *>();
}

Backpack::Backpack(unsigned int c)
{
	this->availabeBudget = c;
	this->budgetUsed = 0;
	this->profit = 0;
	this->collection = vector<Element *>();
}


Backpack::~Backpack() {}

void Backpack::addElement(Element* e)
{
	collection.push_back(e);
	this->budgetUsed += e->getPurchaseCost();
	this->profit += e->getProfitOnSale();
}

void Backpack::displayContents()
{
	cout << "Maksymalna bud¿et to " << this->availabeBudget << endl;
	cout << "Wydano dotychczas " << this->budgetUsed << endl;
	cout << "Suma ze sprzeda¿y " << this->profit << endl;
	cout << "Ilosc sprzedanych przedmiotów " << this->collection.size() << endl;
	system("pause");
}
