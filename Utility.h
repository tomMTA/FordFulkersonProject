#pragma once

#include <string>
#include <vector>

using namespace std;

#define EDMONDS_KARP 1
#define DIJKSTRA 2
#define S 0
#define T 1

namespace utility
{
	void quitWithMsg(const string msg);
	template<typename Type>
	void printVector(vector<Type>);
	void printResult(string method, double maxFlow, vector<vector<int>> minCut, int iterationsCount);
}