#include "stdafx.h"
#include "Backpack.h"


Backpack::Backpack()
{
	this->totalBudget = 0;
	this->budgetUsed = 0;
	this->profit = 0;
	this->collection = vector<Merchandise *>();
}

Backpack::Backpack(unsigned int c)
{
	this->totalBudget = c;
	this->budgetUsed = 0;
	this->profit = 0;
	this->collection = vector<Merchandise *>();
}


Backpack::~Backpack() {}

void Backpack::addMerchandise(Merchandise* e)
{
	collection.push_back(e);
	this->budgetUsed += e->getPurchaseCost();
	this->profit += e->getProfitOnSale();
}

void Backpack::displayContents()
{
	cout << "Maksymalna bud�et to " << this->totalBudget << endl;
	cout << "Wydano dotychczas " << this->budgetUsed << endl;
	cout << "Suma ze sprzeda�y " << this->profit << endl;
	cout << "Ilosc sprzedanych przedmiot�w " << this->collection.size() << endl;
	system("pause");
}
