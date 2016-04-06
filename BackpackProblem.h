#pragma once
#include <random>
#include <stdint.h>
#include <algorithm>
#include "Merchandise.h"
#include "Backpack.h"
#include <iostream>
#include <time.h>

using namespace std;

// Klasa reprezentuj�ca problem plecakowy i algorytmy stworzone do jego rozwiazania
class BackpackProblem
{
private:
	Backpack bag;
	Merchandise* Merchandises;			// tablica wszystkich towr�w
	unsigned size;   // liczba towar�w

public:
	BackpackProblem();
	BackpackProblem(unsigned int s, unsigned int n);
	~BackpackProblem();

	void readFromFile();
	void writeToFile();
	void displayResult();
	void dynamicAlgorithm();
};



