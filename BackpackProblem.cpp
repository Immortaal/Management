#include "stdafx.h"
#include "BackpackProblem.h"
#include <fstream>


// konstruktor domyslny
BackpackProblem::BackpackProblem()
{
	this->bag = Backpack();
	this->amount_elements = 0;
	this->elements = new Element[amount_elements]();
}


// argumenty konstruktora: s- pojemnosc plecaka, n- ilosc wszystkich przedmiotow
BackpackProblem::BackpackProblem(unsigned int s, unsigned int n)
{
	this->bag = Backpack(s);
	this->amount_elements = n;
	this->elements = new Element[amount_elements];

	srand(time(NULL));
	for (int i = 0; i < amount_elements; i++)
	{
		unsigned int a = (rand() / 1000);
		unsigned int b = (rand() / 1000);
		elements[i] = Element(a, b);
	}
}

BackpackProblem::BackpackProblem(const BackpackProblem & backpackProblem)
{
	this->bag = backpackProblem.bag;
	this->amount_elements = backpackProblem.amount_elements;
	elements = new Element[amount_elements];
	for (int i = 0; i < amount_elements; i++){
		elements[i] = backpackProblem.elements[i];
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
	unsigned value, size, capacity;

	fstream file;

	try {
		file.open("dane.txt", std::ios::in);
		file >> this->amount_elements;
		file >> capacity;

		this->elements = new Element[amount_elements];
		this->bag = Backpack(capacity);

		for (unsigned i = 0; i < amount_elements; i++)
		{
			file >> value;
			file >> size;
			
			elements[i] = Element(size, value);
		}

		file.close();
	}
	catch (exception e) {
		cout << "Nie udało sie wczytać pliku!";
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
		cout << "Nie udało sie zapisać do pliku!";
		file.close();
	}
}


// Algorytm oparty na programowaniu dynamicznym
void BackpackProblem::dynamicAlgorithm()
{
	unsigned** bestTable = new unsigned*[amount_elements + 1]; // macierz na podproblemy o wymiarach: [amount_elements+1] x [bag.get_max_capacity()+1]
	for (unsigned i = 0; i < amount_elements + 1; i++) 
	{
		bestTable[i] = new unsigned[bag.get_max_capacity() + 1];
		//tworze iteracyjnie tabele
		for (unsigned j = 0; j <= bag.get_max_capacity(); j++)
		{
			if (i == 0 || j == 0)  // pierwsza kolumne i pierwszy wiersz wypelniamy zerami
			{
				bestTable[i][j] = 0;
			}
	
			else if (elements[i - 1].getSize() <= j)
			{
				unsigned int a = elements[i - 1].getValue() + bestTable[i - 1][j - elements[i - 1].getSize()];
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
	unsigned w = bag.get_max_capacity();
	for (unsigned i = amount_elements; i > 0; i--) 
	{
		if (bestTable[i][w] != bestTable[i - 1][w]) 
		{
			bag.addElement(&elements[i - 1]); // dodanie elementu do plecaka
			w -= elements[i - 1].getSize();
		}
	} 

	// usuwanie macierzy
	for (unsigned i = 0; i < amount_elements; i++) 
	{
		delete[] bestTable[i];
	}
	delete bestTable;
}


BackpackProblem::~BackpackProblem()
{
}


void BackpackProblem::approxAlgorithm()
{

	unsigned int pMax = 0;

	for (int i = 0; i < amount_elements; i++)
	{
		if (elements[i].getValue() > pMax) pMax = elements[i].getValue();
	}

	double scaleK = (0.1 * pMax) / amount_elements;

	Element *scaledCollection = new Element[amount_elements];

	for (int i = 0; i < amount_elements; i++)
	{
		int itemValue = elements[i].getValue();
		int value = (int)floor((double)itemValue / scaleK);
		scaledCollection[i] = Element(elements[i].getSize(), value);
	}

	pMax = 0;

	for (int i = 0; i < amount_elements; i++)
	{
		if (scaledCollection[i].getValue() > pMax) pMax = scaledCollection[i].getValue();
	}

	unsigned int **bestMatrix = new unsigned int *[amount_elements + 1];
	for (int i = 0; i < amount_elements + 1; i++)
	{
		bestMatrix[i] = new unsigned int[amount_elements * pMax];
	}

	for (int k = 0; k < amount_elements; k++) bestMatrix[k][0] = 0;
	for (int y = 0; y < amount_elements * pMax; y++) bestMatrix[0][y] = UINT_MAX;

	unsigned int y = 0;
	unsigned int profit = 0;
	unsigned int pk = 0;
	unsigned int wk = 0;

	do
	{
		y++;
		for (int k = 1; k <= amount_elements; k++)
		{
			Element element = scaledCollection[k - 1];
			pk = element.getValue();
			wk = element.getSize();

			if (y - element.getValue() < 0 || bestMatrix[k - 1][y - pk] == UINT_MAX)
			{
				bestMatrix[k][y] = bestMatrix[k - 1][y];
			}
			else
			{
					
				unsigned int value1 = bestMatrix[k - 1][y];
				unsigned int value2 = bestMatrix[k - 1][y - pk] + wk;

				if (value1 < value2) bestMatrix[k][y] = value1;
				else
					bestMatrix[k][y] = value2;
			}

			if (bestMatrix[k][y] <= bag.get_max_capacity()) profit = y;
		}
	} while (y < amount_elements * pMax);

	cout << "Szacowany zysk: " << (unsigned int)(profit * scaleK) << endl;

	////szukam wartosci w tablicy
	//unsigned w = bag.get_max_capacity();
	//for (unsigned i = amount_elements; i > 0; i--)
	//{
	//	if (bestMatrix[i][w] != bestMatrix[i - 1][w])
	//	{
	//		bag.addElement(&scaledCollection[i - 1]);
	//		w -= elements[i - 1].getSize();
	//	}
	//}

}

//Algorytm typu "Brute force"
void BackpackProblem::bruteForce()
{
	uint64_t table = 1;
	uint64_t bestTable = 0; //zapisuje na 64 bitowym polu - 1 bit reprezentuje 1 rzecz
	uint64_t endOfTable = (table << amount_elements);
	unsigned bestValue = 0;
	while (table < endOfTable) { //dopoki mamy mozliwosc
		uint64_t tmp = 1;
		unsigned tmpValue = 0;
		unsigned tmpWeight = 0; //dodajemy rzeczy, gdy ich bity sa w stanie wysokim
		for (unsigned i = 0; i < amount_elements; i++) {
			bool isSet = table & tmp;
			if (isSet) {
				tmpWeight += elements[i].getSize();
				tmpValue += elements[i].getValue();
			}
			tmp = tmp << 1;
		}
		//sprawdzamy czy lepszy
		if (tmpWeight <= bag.get_max_capacity() && tmpValue > bestValue) {
			bestTable = table;
			bestValue = tmpValue;
		}
		table += 1;
	}
	//przepisujemy graf
	uint64_t tmp = 1;
	for (unsigned i = 0; i < amount_elements; i++) {
		bool isSet = bestTable & tmp;
		if (isSet)
		{
			bag.addElement(&elements[i]);
		}
		tmp = tmp << 1; //przesuwamy maske
	}
}