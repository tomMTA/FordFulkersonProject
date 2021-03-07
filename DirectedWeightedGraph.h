#pragma once
#include "AdjList.h"

class DirectedWeightedGraph
{
private:
	int n;
	double** A;
public:
#define ADD 0
#define SUBTRACT 1
	~DirectedWeightedGraph();
	void MakeEmptyGraph(int n);
	bool IsAdjacent(int u, int v);
	AdjList GetAdjList(int u);
	void AddEdge(int u, int v, double c);
	void RemoveEdge(int u, int v);
	void print();
	int GetNumberOfVertices();
	double GetCapacity(int u, int v);
	void UpdateWeight(double value, int operation, int u, int v);
	DirectedWeightedGraph* CopyGraph();
};