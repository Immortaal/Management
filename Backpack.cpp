#include "Backpack.h"


Backpack::Backpack() : collection(vector<Element *>())
{}

Backpack::Backpack(unsigned int capacity) : max_capacity(capacity),
    collection(vector<Element *>())
{}

Backpack::~Backpack() {}

void Backpack::addElement(Element* element)
{
	collection.push_back(element);
	curr_capacity += element->getWeight();
	values += element->getValue();
}

void Backpack::displayContent()
{
	cout << "Maksymalna waga plecaka to " << this->getMaxCapacity() << endl;
	cout << "Aktualna waga plecaka to  " << this->curr_capacity << endl;
	cout << "Suma wartosci w plecaku to " << this->values << endl;
	cout << "Ilosc przedmiotow w plecaku to " << this->collection.size() << endl;
	//system("pause");
}

const unsigned int Backpack::maxValue()
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
