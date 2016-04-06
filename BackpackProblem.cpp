#include "stdafx.h"
#include "BackpackProblem.h"
#include <fstream>


// konstruktor domyslny
BackpackProblem::BackpackProblem()
{
	this->bag = Backpack();
	this->size = 0;
	this->Merchandises = new Merchandise[size]();
}


// argumenty konstruktora: s- pojemnosc plecaka, n- ilosc wszystkich przedmiotow
BackpackProblem::BackpackProblem(unsigned int s, unsigned int n)
{
	this->bag = Backpack(s);
	this->size = n;
	this->Merchandises = new Merchandise[size];

	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		unsigned int a = (rand() / 1000);
		unsigned int b = (rand() / 1000);
		Merchandises[i] = Merchandise(a, b);
	}
}

// funkcja wyswietlajaca rezultaty dzialania algorytmu
void BackpackProblem::displayResult()
{
	bag.displayContents();
}


// odczyt danych z pliku
void BackpackProblem::readFromFile()
{
	unsigned purchaseCost, sellingPrice, availabeBudget;

	fstream file;

	try {
		file.open("ins_wp5.txt", std::ios::in);
		file >> this->size;
		file >> availabeBudget;

		this->Merchandises = new Merchandise[size];
		this->bag = Backpack(availabeBudget);

		for (unsigned i = 0; i < size; i++)
		{
			file >> purchaseCost;
			file >> sellingPrice;
			Merchandises[i] = Merchandise(purchaseCost, sellingPrice);
		}

		file.close();
	}
	catch (exception e) {
		cout << "Nie uda³o sie wczytaæ pliku!";
		file.close();
	}
}

void BackpackProblem::writeToFile()
{
	fstream file;
	int N = 500;
	srand(time(NULL));

	try {
		file.open("pom.txt", std::ios::out);

		for (unsigned i = 0; i < N; i++)
		{
			unsigned int a = (rand() / 1000);
			unsigned int b = (rand() / 1000);
			file << a << " " << b << endl;
		}

		file.close();
	}
	catch (exception e)
	{
		cout << "Nie uda³o sie zapisaæ do pliku!";
		file.close();
	}
}


// Algorytm oparty na programowaniu dynamicznym
void BackpackProblem::dynamicAlgorithm()
{

	//float
	unsigned** bestTable = new unsigned*[size + 1]; // macierz na podproblemy o wymiarach: [amount_Merchandises+1] x [bag.get_max_capacity()+1]
	for (unsigned i = 0; i < size + 1; i++)
	{
		bestTable[i] = new unsigned[bag.getTotalBudget() + 1];
		//tworze iteracyjnie tabele
		for (unsigned j = 0; j <= bag.getTotalBudget(); j++)
		{
			if (i == 0 || j == 0)  // pierwsza kolumne i pierwszy wiersz wypelniamy zerami
			{
				bestTable[i][j] = 0;
			}

			else if (Merchandises[i - 1].getPurchaseCost() <= j)
			{
				unsigned int a = Merchandises[i - 1].getProfitOnSale() + bestTable[i - 1][j - Merchandises[i - 1].getPurchaseCost()];
				unsigned int b = bestTable[i - 1][j];
				bestTable[i][j] = max(a, b);
			}
			else
			{
				bestTable[i][j] = bestTable[i - 1][j];
			}
		}
	}

	//szukam wartosci w tablicy
	unsigned w = bag.getTotalBudget();

	for (unsigned i = size; i > 0; i--)
	{
		if (bestTable[i][w] != bestTable[i - 1][w]) 
		{
			bag.addMerchandise(&Merchandises[i - 1]); 
			w -= (unsigned)Merchandises[i - 1].getPurchaseCost();
		}
	} 

	// usuwanie macierzy
	for (unsigned i = 0; i < size; i++)
	{
		delete[] bestTable[i];
	}
	delete bestTable;
}


BackpackProblem::~BackpackProblem()
{
}
