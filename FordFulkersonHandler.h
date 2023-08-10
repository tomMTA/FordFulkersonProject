#pragma once
#include "DirectedWeightedGraph.h"
#include "Queue.h"
#include "MaxPriorityQueue.h"
#include <vector>
#include <algorithm>
class FordFulkersonHandler
{
private:
	bool BFS(DirectedWeightedGraph* graph, int s, int t, int parent[]);
	void DFS(DirectedWeightedGraph* graph, int s, vector<bool>* visited);
	void CalculateMinCut(DirectedWeightedGraph* resGraph, int s);
	void InitFlow(DirectedWeightedGraph*& graph, int s, int parent[], double flow[]);
	double Dijkstra(DirectedWeightedGraph* graph, int s, int t, int parent[]);
	void UpdateFlowOnPath(DirectedWeightedGraph* graph, int s, int t, int parent[], double flowOnPath);
	vector<vector<int>>* MinCut = new vector<vector<int>>(2);
public:
	~FordFulkersonHandler();
	double FordFulkersonAlg(DirectedWeightedGraph* graph, int s, int t, short method, int* iterations);
	vector<vector<int>> GetMinCut();
};