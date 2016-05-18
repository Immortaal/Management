#include "stdafx.h"
#include "Aprox.h"

using namespace std;

Aprox::Aprox(Backpack backpack, float errorLimiter)
{
	this->errorLimiter = errorLimiter;
	this->backpack = backpack;

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
		scaledMatrix[i] = new Element(collection[i]->getSize(), scaledValue);
	}

	int y = 0;
	int profit = 0;
		
	//dynamicMatrix = new int[numberOfItems + 1, numberOfItems * pMax];
	unsigned** bestTable = new unsigned*[collection.size() + 1];
	for (unsigned i = 0; i < +1; i++)
	{
		bestTable[i] = new unsigned[collection.size() * backpack.maxValue()];
	}


}

/*
	public int calculateSolution()
        {
            Item[] scaledMatrix = new Item[backpack.matrix.Count()];
            for(int i = 0; i < backpack.matrix.Count(); i++)
            {
                int itemValue = backpack.matrix[i].Value;
                int value = (int) Math.Floor((decimal)itemValue / (decimal)scaleK);
                scaledMatrix[i] = new Item(backpack.matrix[i].Weight, value);
            }

          
            Backpack newBackpack = new Backpack(backpack.Capasity, scaledMatrix);
            dynamic = new DynamicAlgorithm(newBackpack);

            int profit = (int)(dynamic.Dynamic() * scaleK);
            return profit;
            
        }

		int y = 0;
		int profit = 0;
		do
		{
		y = y + 1;
		for (int k = 1; k <= numberOfItems; k++)
		{
		Item item = getItem(k - 1);
		if (y - item.Value < 0 || dynamicMatrix[k - 1, y - item.Value] == int.MaxValue) dynamicMatrix[k, y] = dynamicMatrix[k - 1, y];
		else
		dynamicMatrix[k, y] = minValue(k, y, item);

		if (dynamicMatrix[k, y] <= backpack.Capasity) profit = y;
		}
		}
		while (y < (numberOfItems * pMax) - 1);

		return profit;
		}

		private int minValue(int k, int y, Item item)
		{
		int value1 = dynamicMatrix[k - 1, y];
		int value2 = dynamicMatrix[k - 1, y - item.Value] + item.Weight;

		if (value1 < value2) return value1;

		return value2;
		}
*/
