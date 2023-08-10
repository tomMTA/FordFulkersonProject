#include <string>
#include <iostream>
#include "Utility.h"

using namespace std;

void utility::quitWithMsg(const string msg)
{
	cout << msg << endl;
	system("pause");
	exit(1);
}

template<typename Type>
void utility::printVector(vector<Type> vector)
{
	cout << "[";
	for (int i = 0; i < vector.size(); i++)
	{
		cout << vector[i];
		if (i < vector.size() - 1)
		{
			cout << ", ";
		}
	}
	cout << "]. ";
}

void utility::printResult(string method, double maxFlow, vector<vector<int>> minCut, int iterationsCount)
{
	cout << method << " Method:\n"
		<< "Max flow = "
		<< maxFlow
		<< "\n";

	cout << "Min cut: " << "S = ";
	printVector(minCut[S]);
	cout << "T = ";
	printVector(minCut[T]);
	cout << endl;

	cout << "Number of iterations: "
		<< iterationsCount
		<< "\n\n";
}
