#pragma once
#include "AdjList.h"

class DirectedWeightedGraph
{
private:
	int n;
	double** adjMatrix;
public:
	DirectedWeightedGraph(int n);
	~DirectedWeightedGraph();
	DirectedWeightedGraph* CopyGraph();
	bool IsAdjacent(int u, int v);
	AdjList GetAdjList(int u);
	void AddEdge(int u, int v, double capacity);
	void RemoveEdge(int u, int v);
	void Print();
	int GetNumberOfVertices();
	double GetCapacity(int u, int v);
	void AddWeight(int u, int v, double value);
};