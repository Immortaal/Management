#pragma once
#include "stdafx.h"
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "BackpackProblem.h"


using namespace std;
static double PCFreq = 0.0;
static __int64 CounterStart = 0;


void static StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

double static GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq; // czas w ms
}


// funkcja mierzaca czas dzialania algorytmu i zapisujaca go w pliku
void static measure()
{
	BackpackProblem backpackProblem = BackpackProblem(500, 100);
	fstream plik;
	plik.open("pomiary500_100.txt", ios::out);
	if (plik.good() == true)
	{
		for (int i = 0; i < 100; i++)
		{
			StartCounter();
			backpackProblem.dynamicAlgorithm();
			plik << GetCounter() << "\n";
		}
	}
	plik.close();
	cout << "done";
}