#include <iostream>

#include "BackpackProblem.h"

using namespace std;

int main(int argc, char *argv[])
{
    BackpackProblem pr = BackpackProblem();
	//pr.writeToFile();
	pr.readFromFile();
	pr.approxAlgorithm();
	//pr.dynamicAlgorithm();
	//pr.bruteForce();
	//pr.displayResult();
    cout << "done" << endl;
	//system("pause");
	return 0;
}
