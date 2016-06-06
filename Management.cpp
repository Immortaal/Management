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

std::vector<string> bruteResults;
std::vector<string> dynamicResults;
std::vector<string> aproxResults;

int threads;

void threadFinished()
{
	std::unique_lock<std::mutex> lock(mtx);
	threads--;
	if (threads == 0)
	{
		threads_working.notify_one();
	}
}

void bruteSave(long long duration)
{
	std::unique_lock<std::mutex> lock(mtx);
	try {
		bruteFile.open("brute.txt", std::ios::app);

		bruteFile << duration << endl;
		bruteTimes.push_back(duration);
		bruteFile.close();
	}
	catch (exception e)
	{
		bruteFile.close();
	}

}

void bruteSaveResults(std::string data)
{
	std::unique_lock<std::mutex> lock(mtx);
	bruteResults.push_back(data);

}

void dynamicSave(long long duration){
	std::unique_lock<std::mutex> lock(mtx);

	try {
		dynamicFile.open("dynamic.txt", std::ios::app);

		dynamicFile << duration << endl;
		dynamicTimes.push_back(duration);
		dynamicFile.close();
	}
	catch (exception e)
	{
	
		dynamicFile.close();
	}

}

void dynamicSaveResults(std::string data)
{
	std::unique_lock<std::mutex> lock(mtx);
	dynamicResults.push_back(data);

}

void aproxSave(long long duration){
	std::unique_lock<std::mutex> lock(mtx);

	try {
		aproxFile.open("aprox.txt", std::ios::app);

		aproxFile << duration << endl;
		aproxTimes.push_back(duration);
		aproxFile.close();
	}
	catch (exception e)
	{

		aproxFile.close();
	}

}

void aproxSaveResults(std::string data)
{
	std::unique_lock<std::mutex> lock(mtx);
	aproxResults.push_back(data);

}


void brute(const BackpackProblem & backpackProblem){
	BackpackProblem brutePR(backpackProblem);
	auto start_time = chrono::high_resolution_clock::now();
	
	for (int i = 0; i < 10; i++)
	{
		brutePR.bruteForce();
		//bruteSaveResults(brutePR.results());
	}

	auto end_time = chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	//bruteTimes.push_back(duration);
	//bruteSave(duration);
	bruteTimes.push_back(duration);
	threadFinished();

}

void dynamic(const BackpackProblem & backpackProblem){
	BackpackProblem dynamicPR(backpackProblem);
	auto start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < 10; i++)
	{
		dynamicPR.dynamicAlgorithm();
		//dynamicSaveResults(dynamicPR.results());
	}
	auto end_time = chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	//dynamicSave(duration);
	dynamicTimes.push_back(duration);
	threadFinished();
	//dynamicTimes.push_back(duration);
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

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

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
		bruteResults.push_back(bp.results());
	}

	auto end_time = chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	cout << "\n1. Bruteforce: " << duration << endl;

	start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < 100; i++){
		bp.dynamicAlgorithm();
		dynamicResults.push_back(bp.results());
	}
	end_time = chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	cout << "2. Programowanie dynamiczne: " << duration << endl;

	start_time = chrono::high_resolution_clock::now();

	for (int i = 0; i < 30; i++)
	{
		int result = bp.approxAlgorithm();
		aproxResults.push_back(to_string(result));
	}

	cout << "3. Algorytm aproksymacyjny: " << duration << endl;

	end_time = chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
	
	//std::cout << "\nCzas wykonywania zadan bez watkow: " << duration << " ms" << std::endl;
	std::system("PAUSE");
}


void finalCalulations(BackpackProblem bp){
	std::unique_lock<std::mutex> lock(mtx);
	threads_working.wait(lock, []
	{
		return threads == 0;
	});

	cout << "Czasy wykonywania watkow (w ms): " << endl;
	
	long long maxTime = 0;
	long long maxBrute = 0;
	long long maxDynamic = 0;
	long long maxAprox = 0;

	for (int i = 0; i < bruteTimes.size(); i++){
		
		if (bruteTimes[i] > maxTime){
			maxTime = bruteTimes[i];
			maxBrute = bruteTimes[i];
		}
	}
	cout << "1. Bruteforce: " << maxBrute << endl;;
	
	for (int i = 0; i < dynamicTimes.size(); i++){
	
		if (dynamicTimes[i] > maxTime){
			maxTime = dynamicTimes[i];
			maxDynamic = dynamicTimes[i];
		}
	}
	cout << "2. Programowanie dynamiczne: " << maxDynamic << endl;;

	
	for (int i = 0; i < aproxTimes.size(); i++){
		//cout << aproxTimes[i] << " ";
		if (aproxTimes[i] > maxTime){
			maxTime = aproxTimes[i];
			maxAprox = aproxTimes[i];
		}
	}
	cout << "3. Algorytm aproksymacyjny: " << maxAprox << endl;

	//std::cout << "Czas wykonywania algorytmow z watkami: " << maxTime << " ms" << std::endl;
	noThreads(bp);
	
}

int _tmain(int argc, _TCHAR* argv[])
{
	BackpackProblem bp;
	bp.readFromFile();

	threads = 23;

	std::thread bruteThread1(brute, bp);
	std::thread bruteThread2(brute, bp);
	std::thread bruteThread3(brute, bp);
	std::thread bruteThread4(brute, bp);
	std::thread bruteThread5(brute, bp);
	std::thread bruteThread6(brute, bp);
	std::thread bruteThread7(brute, bp);
	std::thread bruteThread8(brute, bp);
	std::thread bruteThread9(brute, bp);
	std::thread bruteThread10(brute, bp);

	std::thread dynamicThread1(dynamic, bp);
	std::thread dynamicThread2(dynamic, bp);
	std::thread dynamicThread3(dynamic, bp);
	std::thread dynamicThread4(dynamic, bp);
	std::thread dynamicThread5(dynamic, bp);
	std::thread dynamicThread6(dynamic, bp);
	std::thread dynamicThread7(dynamic, bp);
	std::thread dynamicThread8(dynamic, bp);
	std::thread dynamicThread9(dynamic, bp);
	std::thread dynamicThread10(dynamic, bp);


	std::thread aproxThread1(aprox, bp);
	std::thread aproxThread2(aprox, bp);
	std::thread aproxThread3(aprox, bp);
	
	bruteThread1.join();
	bruteThread2.join();
	bruteThread3.join();
	bruteThread4.join();
	bruteThread5.join();
	bruteThread6.join();
	bruteThread7.join();
	bruteThread8.join();
	bruteThread9.join();
	bruteThread10.join();

	dynamicThread1.join();
	dynamicThread2.join();
	dynamicThread3.join();
	dynamicThread4.join();
	dynamicThread5.join();
	dynamicThread6.join();
	dynamicThread7.join();
	dynamicThread8.join();
	dynamicThread9.join();
	dynamicThread10.join();

	aproxThread1.join();
	aproxThread2.join();
	aproxThread3.join();

	finalCalulations(bp);

	return 0;
}

