#include <iostream>

#include "BackpackProblem.h"

using namespace std;

int main(int argc, char *argv[])
{
    BackpackProblem pr = BackpackProblem();
	//pr.writeToFile();
	pr.readFromFile();
	//pr.approxAlgorithm();
	int res = pr.skalowanie();
    cout << "wyszlo " << res  << endl;
    //pr.dynamicAlgorithm();
	//pr.bruteForce();
	pr.displayResult();
	//system("pause");
	return 0;
}
