// Management.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BackpackProblem.h"


int _tmain(int argc, _TCHAR* argv[])
{
	BackpackProblem pr = BackpackProblem();
	pr.writeToFile();
	cout << "done" << endl;
	system("pause");
	return 0;
}

