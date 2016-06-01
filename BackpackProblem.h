#pragma once
#include <random>
#include <stdint.h>
#include <algorithm>
#include "Element.h"
#include "Backpack.h"
#include <iostream>
#include <time.h>

using namespace std;

//BackpackProblem structure and solution alorithms
class BackpackProblem
{
private:
	Backpack bag;
    std::vector<Element> elements;
    unsigned elementCount;
public:
	BackpackProblem();
	BackpackProblem(unsigned int s, unsigned int n);
	~BackpackProblem();
	void readFromFile();
	void writeToFile();
	void displayResult();

	void dynamicAlgorithm();
	void approxAlgorithm();
	void bruteForce();

    int p_max(int val[], int n);
    int pp_max();
    int algorytm_dokladny(int p_max, std::vector<int>& wartosci);
    int skalowanie();
};



