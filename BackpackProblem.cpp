#include "BackpackProblem.h"
#include <fstream>

BackpackProblem::BackpackProblem() : bag(), elementCount(0),
    elements(std::vector<Element>(0))
{
}

BackpackProblem::BackpackProblem(unsigned int s, unsigned int n) : bag(s), elementCount(n),
    elements(std::vector<Element>(n))
{
	srand(time(NULL));
	for (int i = 0; i < elementCount; i++)
	{
		unsigned int a = (rand() / 1000);
		unsigned int b = (rand() / 1000);
		elements[i] = Element(a, b);
	}
}

// funkcja wyswietlajaca rezultaty dzialania algorytmu
void BackpackProblem::displayResult()
{
	bag.displayContent();
}


// odczyt danych z pliku
void BackpackProblem::readFromFile()
{
	unsigned value, size, capacity;

	fstream file;

	try {
		file.open("dane4.txt", std::ios::in);
		file >> this->elementCount;
		file >> capacity;

		this->elements = std::vector<Element>(elementCount);//new Element[amount_elements];
		this->bag = Backpack(capacity);

		for (unsigned i = 0; i < elementCount; i++)
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
	//unsigned** bestTable = new unsigned*[elementCount + 1]; // macierz na podproblemy o wymiarach: [amount_elements+1] x [bag.get_max_capacity()+1]
	std::vector < std::vector<unsigned> > bestTable(elementCount + 1);

    for (unsigned i = 0; i < elementCount + 1; i++)
	{
		//bestTable[i] = new unsigned[bag.getMaxCapacity() + 1];
        bestTable[i] = std::vector<unsigned>(bag.getMaxCapacity() + 1);
		//tworze iteracyjnie tabele
		for (unsigned j = 0; j <= bag.getMaxCapacity(); j++)
		{
			if (i == 0 || j == 0)  // pierwsza kolumne i pierwszy wiersz wypelniamy zerami
			{
				bestTable[i][j] = 0;
			}

			else if (elements[i - 1].getWeight() <= j)
			{
				unsigned int a = elements[i - 1].getValue() + bestTable[i - 1][j - elements[i - 1].getWeight()];
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
	unsigned w = bag.getMaxCapacity();
	for (unsigned i = elementCount; i > 0; i--)
	{
		if (bestTable[i][w] != bestTable[i - 1][w])
		{
			bag.addElement(&elements[i - 1]); // dodanie elementu do plecaka
			w -= elements[i - 1].getWeight();
		}
	}

	// usuwanie macierzy
	//for (unsigned i = 0; i < elementCount; i++)
	//{
	//	delete[] bestTable[i];
	//}
	//delete bestTable;
}


BackpackProblem::~BackpackProblem()
{
}

int BackpackProblem::p_max(int val[], int n)
{
	int p_max = val[0];
	for (int i = 0; i < n; i++)
	{
		if (val[i] > p_max)
		{
			p_max = val[i];
		}
	}
	return p_max;
}

int BackpackProblem::algorytm_dokladny(int p_max, std::vector<int>& wartosci)
{
	int **F = new int *[elementCount + 1]; // tworzenie tablicy dwuwymiarowej dla funkcji F
	int wynik = 0;
    int W = bag.getMaxCapacity();

	for (int k = 0; k<(elementCount + 1); k++)
	{
		F[k] = new int[elementCount*p_max]; // zapelnianie kazdego wiersza - inicjacja tablicy
		F[k][0] = 0;
	}

	for (int y = 1; y <= elementCount*p_max; y++)
	{
		F[0][y] = std::numeric_limits<unsigned int>::max();

	}

	for (int k = 1; k <= elementCount; k++)
		for (int y = 1; y <= elementCount*p_max; y++)
		{
			if (y - wartosci[k - 1] < 0 || F[k - 1][y - wartosci[k - 1]] == std::numeric_limits<unsigned int>::max())
			{
				F[k][y] = F[k - 1][y];
			}

			else
			{
				F[k][y] = min((unsigned)F[k - 1][y], F[k - 1][y - wartosci[k - 1]] + elements[k - 1].getWeight());
			}

			if (F[elementCount][y] <= W)
			{
				wynik = y;
			}
		}

	return wynik;
}

int BackpackProblem::pp_max() {
    int max = elements[0].getValue();
	for (int i = 0; i < elementCount; i++)
	{
		if (elements[i].getValue() > max)
		{
			max = elements[i].getValue();
		}
	}
	return max;
}

int BackpackProblem::skalowanie()
{
    double blad = 0.1;
	double K = (blad * pp_max()) / (float)elementCount;
	if (K < 1)
	{
		K = 1;
	}

    std::vector<int> wartosci(elementCount);
	for (int i = 0; i < elementCount; i++)
	{
		wartosci[i] = floor(elements[i].getValue() / K);
	}

	int p_max = floor(pp_max() / K) + 1;

	return (K * algorytm_dokladny(p_max, wartosci));
}



void BackpackProblem::approxAlgorithm()
{

    std::cout << "In approx\n";
	unsigned int pMax = 0;

	for (int i = 0; i < elementCount; i++)
	{
		if (elements[i].getValue() > pMax) pMax = elements[i].getValue();
	}

	double scaleK = (0.1 * pMax) / elementCount;

	//Element *scaledCollection = new Element[elementCount];
    std::vector<Element> scaledCollection(elementCount);

	for (int i = 0; i < elementCount; i++)
	{
		int itemValue = elements[i].getValue();
		int value = (int)floor((double)itemValue / scaleK);
		scaledCollection[i] = Element(elements[i].getWeight(), value);
	}

	pMax = 0;

	for (int i = 0; i < elementCount; i++)
	{
		if (scaledCollection[i].getValue() > pMax) pMax = scaledCollection[i].getValue();
	}

	//unsigned int **bestMatrix = new unsigned int *[elementCount + 1];
    std::vector< std::vector<unsigned> > bestMatrix(elementCount +1);
	for (int i = 0; i < elementCount + 1; i++)
	{
		//bestMatrix[i] = new unsigned int[elementCount * pMax];
        bestMatrix[i] = std::vector<unsigned>(elementCount * pMax);
	}

	for (int k = 0; k < elementCount; k++) bestMatrix[k][0] = 0;
	for (int y = 0; y < elementCount * pMax; y++) bestMatrix[0][y] = std::numeric_limits<unsigned int>::max();

	int y = 0;
	unsigned int profit = 0;
	int pk = 0;
	unsigned int wk = 0;

    std::cout << "before loop!" << std::endl;
	do
	{
		y++;
		for (int k = 1; k <= elementCount; k++)
		{
			Element element = scaledCollection[k - 1];
			pk = element.getValue();
			wk = element.getWeight();

            if (5 > 10) {
            } else {
                if (y - element.getValue() < 0 || bestMatrix[k - 1][std::max(0, y - pk)] == std::numeric_limits<unsigned int>::max())
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
            }


			if (bestMatrix[k][y] <= bag.getMaxCapacity()) profit = y;
		}
	} while (y < elementCount * pMax);

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
	uint64_t endOfTable = (table << elementCount);
	unsigned bestValue = 0;
	while (table < endOfTable) { //dopoki mamy mozliwosc
		uint64_t tmp = 1;
		unsigned tmpValue = 0;
		unsigned tmpWeight = 0; //dodajemy rzeczy, gdy ich bity sa w stanie wysokim
		for (unsigned i = 0; i < elementCount; i++) {
			bool isSet = table & tmp;
			if (isSet) {
				tmpWeight += elements[i].getWeight();
				tmpValue += elements[i].getValue();
			}
			tmp = tmp << 1;
		}
		//sprawdzamy czy lepszy
		if (tmpWeight <= bag.getMaxCapacity() && tmpValue > bestValue) {
			bestTable = table;
			bestValue = tmpValue;
		}
		table += 1;
	}
	//przepisujemy graf
	uint64_t tmp = 1;
	for (unsigned i = 0; i < elementCount; i++) {
		bool isSet = bestTable & tmp;
		if (isSet)
		{
			bag.addElement(&elements[i]);
		}
		tmp = tmp << 1; //przesuwamy maske
	}
}
