#pragma once
#include <random>
#include <stdint.h>
#include <algorithm>
#include "Element.h"
#include "Backpack.h"
#include <iostream>
#include <time.h>
#include <string>
#include <vector>


using namespace std;


// Klasa reprezentująca problem plecakowy i algorytmy stworzone do jego rozwiazania
class BackpackProblem
{
private:
	Backpack bag;
	Element* elements; // tablica wszystkich elementow
	unsigned amount_elements; // liczba elementow

	unsigned int maxValue();

public:
	BackpackProblem();
	BackpackProblem(unsigned int s, unsigned int n);
	BackpackProblem(const BackpackProblem & backpackProblem);

	~BackpackProblem();
	void readFromFile();
	void writeToFile();
	void displayResult();
	string results();

	void dynamicAlgorithm();
	unsigned int approxAlgorithm();
	void bruteForce();
};



