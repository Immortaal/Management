#pragma once
#include <random>
#include <stdint.h>
#include <algorithm>
#include "Merchandise.h"
#include "Backpack.h"
#include <iostream>
#include <time.h>

using namespace std;

// Klasa reprezentuj¹ca problem plecakowy i algorytmy stworzone do jego rozwiazania
class BackpackProblem
{
private:
	Backpack bag;
	Merchandise* Merchandises;			// tablica wszystkich towrów
	unsigned size;   // liczba towarów

public:
	BackpackProblem();
	BackpackProblem(unsigned int s, unsigned int n);
	~BackpackProblem();

	void readFromFile();
	void writeToFile();
	void displayResult();
	void dynamicAlgorithm();
};



