#pragma once

#include <ctime>
#include <iostream>
#include <fstream>
#include <chrono>
#include "BackpackProblem.h"


using namespace std;

// funkcja mierzaca czas dzialania algorytmu i zapisujaca go w pliku
void static measure()
{
	BackpackProblem backpackProblem = BackpackProblem(500, 100);
	fstream plik;
	plik.open("dane.txt", ios::out);
	if (plik.good() == true)
	{
		for (int i = 0; i < 100; i++)
		{
            std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
			backpackProblem.dynamicAlgorithm();
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
			plik << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "\n";
		}
	}
	plik.close();
	cout << "done";
}
