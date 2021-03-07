#include "DirectedWeightedGraph.h"
#include <iostream>
using namespace std;

DirectedWeightedGraph::~DirectedWeightedGraph()
{
	for (int i = 0; i < n; i++)
	{
		delete[]A[i];
	}
	delete[]A;
}

void DirectedWeightedGraph::MakeEmptyGraph(int n)
{
	this->n = n;
	A = new double* [n];
	for (int i = 0; i < n; i++)
	{
		A[i] = new double[n];
		for (int j = 0; j < n; j++)
			A[i][j] = 0;
	}
}

bool DirectedWeightedGraph::IsAdjacent(int u, int v)
{
	return A[u - 1][v - 1] != 0;
}

AdjList DirectedWeightedGraph::GetAdjList(int u)
{
	AdjList list;
	for (int i = 0; i < n; i++)
		if (A[u - 1][i] != 0)
			list.Append(i + 1);
	return list;
}

void DirectedWeightedGraph::AddEdge(int u, int v, double c)
{
	if (u != v) //no loops allowed in G
		A[u - 1][v - 1] = c;
}

void DirectedWeightedGraph::RemoveEdge(int u, int v)
{
	A[u - 1][v - 1] = 0;
}

void DirectedWeightedGraph::print()
{
	for (int i = 0; i < n; i++)
	{
		cout << "|\t";
		for (int j = 0; j < n; j++)
			cout << A[i][j] << '\t';
		cout << '|' << endl << endl;
	}
	cout << endl;
}

int DirectedWeightedGraph::GetNumberOfVertices()
{
	return n;
}

double DirectedWeightedGraph::GetCapacity(int u, int v)
{
	return A[u - 1][v - 1];
}


void DirectedWeightedGraph::UpdateWeight(double value, int operation, int u, int v)
{
	// 0 for addition, 1 for subtraction. 
	switch (operation)
	{
	case ADD:
		A[u - 1][v - 1] += value;
		break;
	case SUBTRACT:
		A[u - 1][v - 1] -= value;
	default:
		break;
	}
}

DirectedWeightedGraph* DirectedWeightedGraph::CopyGraph()
{
	DirectedWeightedGraph* copy = new DirectedWeightedGraph();
	copy->MakeEmptyGraph(n);
	for (int u = 0; u < n; u++)
		for (int v = 0; v < n; v++)
			copy->A[u][v] = A[u][v];
	return copy;
}
