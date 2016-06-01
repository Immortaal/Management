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


std::mutex mtx;
fstream bruteFile;
fstream dynamicFile;
fstream aproxFile;

void bruteSave(long long duration)
{
	std::unique_lock<std::mutex> lock(mtx);
	try {
		bruteFile.open("brute.txt", std::ios::app);

		bruteFile << duration << endl;
		bruteFile.close();
	}
	catch (exception e)
	{
		bruteFile.close();
	}

}

void dynamicSave(long long duration){
	std::unique_lock<std::mutex> lock(mtx);

	try {
		dynamicFile.open("dynamic.txt", std::ios::app);

		dynamicFile << duration << endl;
		dynamicFile.close();
	}
	catch (exception e)
	{
	
		dynamicFile.close();
	}

}

void aproxSave(long long duration){
	std::unique_lock<std::mutex> lock(mtx);

	try {
		aproxFile.open("aprox.txt", std::ios::app);

		aproxFile << duration << endl;
		aproxFile.close();
	}
	catch (exception e)
	{

		aproxFile.close();
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

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	bruteSave(duration);

}

void dynamic(const BackpackProblem & backpackProblem){
	BackpackProblem dynamicPR(backpackProblem);
	auto start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < 10; i++)
	{
		dynamicPR.dynamicAlgorithm();
	}
	auto end_time = chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	dynamicSave(duration);

}

void aprox(const BackpackProblem & backpackProblem){

	BackpackProblem aproxPR(backpackProblem);
	auto start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < 10; i++)
	{
		aproxPR.approxAlgorithm();
	}
	auto end_time = chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

	aproxSave(duration);
}

int _tmain(int argc, _TCHAR* argv[])
{
	BackpackProblem bp;
	bp.readFromFile();

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
	//std::thread aproxThread4(aprox, bp);
	//std::thread aproxThread5(aprox, bp);

	/*
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	auto duration =  std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		*/
	
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
	/*aproxThread4.join();
	aproxThread5.join();*/

	
	return 0;
}

