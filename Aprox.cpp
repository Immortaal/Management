#include "Aprox.h"

using namespace std;

#include <cmath>

Aprox::Aprox(Backpack backpack, float errorLimiter) : backpack(backpack), errorLimiter(errorLimiter)
{
	scale = ( errorLimiter * backpack.maxValue() ) / backpack.numberOfProducts();
}

Aprox::~Aprox()
{
}

void Aprox::calculate()
{
	std::vector<Element *> collection = backpack.getCollection();
	std::vector<Element *> scaledMatrix = std::vector<Element *>(collection.size());

	for (int i = 0; i < collection.size(); i++)
	{
		unsigned int itemValue = collection[i]->getValue();
		unsigned int scaledValue = (unsigned int)floor(itemValue / scale);
		scaledMatrix[i] = new Element(collection[i]->getWeight(), scaledValue);
	}

	int y = 0;
	int profit = 0;

    unsigned** bestTable = new unsigned*[collection.size() + 1];
	for (unsigned i = 0; i < +1; i++)
	{
		bestTable[i] = new unsigned[collection.size() * backpack.maxValue()];
	}
}
