// Management.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BackpackProblem.h"
#include <thread>
#include <chrono>

void brute(const BackpackProblem & backpackProblem){
	BackpackProblem brutePR(backpackProblem);
	auto start_time = chrono::high_resolution_clock::now();
	for (int i = 0; i < 10; i++)
	{
		brutePR.bruteForce();
	}
	auto end_time = chrono::high_resolution_clock::now();
	
}

void dynamic(const BackpackProblem & backpackProblem){
	BackpackProblem dynamicPR(backpackProblem);
	for (int i = 0; i < 10; i++)
	{
		dynamicPR.dynamicAlgorithm();
	}

}

void aprox(const BackpackProblem & backpackProblem){

	BackpackProblem aproxPR(backpackProblem);

	for (int i = 0; i < 10; i++)
	{
		aproxPR.approxAlgorithm();
	}
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
	std::thread aproxThread4(aprox, bp);
	std::thread aproxThread5(aprox, bp);

	
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
	aproxThread4.join();
	aproxThread5.join();

	
	return 0;
}

