#include "stdafx.h"
#include "Backpack.h"


Backpack::Backpack()
{
	this->max_capacity = 0;
	this->curr_capacity = 0;
	this->values = 0;
	this->collection = vector<Element *>();
}

Backpack::Backpack(unsigned int c)
{
	this->max_capacity = c;
	this->curr_capacity = 0;
	this->values = 0;
	this->collection = vector<Element *>();
}


Backpack::~Backpack() {}

void Backpack::addElement(Element* e)
{
	collection.push_back(e);
	this->curr_capacity += e->getSize();
	this->values += e->getValue();
}

void Backpack::displayContents()
{
	cout << "Maksymalna waga plecaka to " << this->get_max_capacity() << endl;
	cout << "Aktualna waga plecaka to  " << this->curr_capacity << endl;
	cout << "Suma wartosci w plecaku to " << this->values << endl;
	cout << "Ilosc przedmiotow w plecaku to " << this->collection.size() << endl;
	system("pause");
}

unsigned int Backpack::maxValue()
{
	unsigned int maxVal = 0;

	for (int i = 0; i < collection.size(); i++)
	{
		if (collection[i]->getValue() > maxVal)
		{
			maxVal = collection[i]->getValue();
		}
	}

	return maxVal;

}

Element *Backpack::elementAt(int index)
{
	return collection[index];
}
