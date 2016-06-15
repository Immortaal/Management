// Management.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BackpackProblem.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <vector>
#include <iostream>


std::condition_variable threads_working;
std::mutex mtx;
fstream bruteFile;
fstream bruteFileResults;
fstream dynamicFile;
fstream dynamicFileResults;
fstream aproxFile;
fstream aproxFileResults;

std::vector<long long> bruteTimes;
std::vector<long long> dynamicTimes;
std::vector<long long> aproxTimes;

int threads;
int tasks = 10;

void threadFinished()
{
	std::unique_lock<std::mutex> lock(mtx);
	threads--;
	if (threads == 0)
	{
		threads_working.notify_one();
	}
}


void brute(const BackpackProblem & backpackProblem){
	BackpackProblem brutePR(backpackProblem);
	auto start_time = chrono::high_resolution_clock::now();
	
	for (int i = 0; i < 10; i++)
	{
		brutePR.bruteForce();
	}

	auto end_time = chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

	bruteTimes.push_back(duration);
	threadFinished();

}

void dynamic(const BackpackProblem & backpackProblem){
	BackpackProblem dynamicPR(backpackProblem);
	auto start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < 10; i++)
	{
		dynamicPR.dynamicAlgorithm();
	}
	auto end_time = chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

	dynamicTimes.push_back(duration);
	threadFinished();
	
}

void aprox(const BackpackProblem & backpackProblem){

	BackpackProblem aproxPR(backpackProblem);
	auto start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < 10; i++)
	{
		unsigned int result = aproxPR.approxAlgorithm();
		//aproxSaveResults(to_string(result));
	}
	auto end_time = chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

	//aproxSave(duration);
	threadFinished();
	aproxTimes.push_back(duration);
}

void noThreads(BackpackProblem bp)
{

	cout << "\n\nAlgorytmy wykonywane sekwencyjne: ";
	auto start_time = chrono::high_resolution_clock::now();

	for (int i = 0; i < 100; i++)
	{
		bp.bruteForce();
	}

	auto end_time = chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();

	cout << "\n1. Bruteforce: " << duration << " microseconds" << endl;


	auto start_time2 = chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++)
	{
		bp.dynamicAlgorithm();
	}
	auto end_time2 = chrono::high_resolution_clock::now();
	auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end_time2 - start_time2).count();

	cout << "2. Programowanie dynamiczne: " << duration2 << " microseconds"<< endl;



	auto start_time3 = chrono::high_resolution_clock::now();

	for (int i = 0; i < 100; i++)
	{
		bp.approxAlgorithm();
	}
	auto end_time3 = chrono::high_resolution_clock::now();
	auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end_time3 - start_time3).count();

	cout << "3. Algorytm aproksymacyjny: " << duration3 << " microseconds" << endl;

	std::system("PAUSE");
}

void finalCalulations(BackpackProblem bp){
	std::unique_lock<std::mutex> lock(mtx);
	threads_working.wait(lock, []
	{
		return threads == 0;
	});

	cout << "Ilosc zadan dla kazdego algorytmu: " << tasks * 10 << endl;
	cout << "Czasy wykonywania watkow: " << endl;
	
	long long maxBrute = 0;
	long long maxDynamic = 0;
	long long maxAprox = 0;

	for (int i = 0; i < bruteTimes.size(); i++){
		
		if (bruteTimes[i] > maxBrute){
			maxBrute = bruteTimes[i];
		}
	}
	cout << "1. Bruteforce: " << maxBrute << " mikrosekund"<< endl;;
	
	for (int i = 0; i < dynamicTimes.size(); i++){
	
		if (dynamicTimes[i] > maxDynamic){
		
			maxDynamic = dynamicTimes[i];
		}
	}
	cout << "2. Programowanie dynamiczne: " << maxDynamic << " mikrosekund "  << endl;;

	for (int i = 0; i < aproxTimes.size(); i++){
		if (aproxTimes[i] > maxAprox){
			maxAprox = aproxTimes[i];
		}
	}
	cout << "3. Algorytm aproksymacyjny: " << maxAprox << " mikrosekund " << endl;

	noThreads(bp);
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	BackpackProblem bp;
	bp.readFromFile();

	threads = 30;

	std::vector<std::thread *> bruteThreads(tasks);
	std::vector<std::thread *> dynamicThreads(tasks);
	std::vector<std::thread *> aproxThreads(tasks);

	for (int i = 0; i < dynamicThreads.size(); i++)
	{
		dynamicThreads[i] = new std::thread(dynamic, bp);
		//dynamicThreads[i]->join();
	}

	for (int i = 0; i < bruteThreads.size(); i++)
	{
		bruteThreads[i] = new std::thread(brute, bp);
		//bruteThreads[i]->join();
	}

	for (int i = 0; i < aproxThreads.size(); i++)
	{
		aproxThreads[i] = new std::thread(aprox, bp);
		//aproxThreads[i]->join();
	}

	finalCalulations(bp);

	return 0;
}

