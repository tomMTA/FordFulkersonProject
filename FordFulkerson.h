#pragma once
#include "DirectedWeightedGraph.h"
#include "Queue.h"
#include "MaxPriorityQueue.h"
#include <vector>
#include <algorithm>
class FordFulkerson
{
private:
	bool BFS(DirectedWeightedGraph* graph, int s, int t, int parent[]);
	void DFS(DirectedWeightedGraph* graph, int s, vector<bool>* visited);
	void FindMinCut(DirectedWeightedGraph* resGraph, int s);
	void INIT(DirectedWeightedGraph*& graph, int s, int* parent, double* d);
	double DIJKSTRA(DirectedWeightedGraph* graph, int s, int t, int parent[]);
	void UpdatePath(DirectedWeightedGraph* graph, int s, int t, int* parent, double flowOnPath);
	vector<vector<int>>* MinCut = new vector<vector<int>>(2);
#define S 0
#define T 1
public:
	~FordFulkerson();
	double FordFulkersonAlg(DirectedWeightedGraph* graph, int s, int t, short method, int* iterations);
	void PrintMinCut();
#define _BFS 1
#define _GREEDY 2
};