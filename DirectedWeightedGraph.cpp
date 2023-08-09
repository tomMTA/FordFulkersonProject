#include "DirectedWeightedGraph.h"
#include <iostream>
using namespace std;

DirectedWeightedGraph::DirectedWeightedGraph(int n)
{
	this->n = n;
	this->adjMatrix = new double* [n];
	for (int i = 0; i < n; i++)
	{
		this->adjMatrix[i] = new double[n];
		for (int j = 0; j < n; j++)
		{
			this->adjMatrix[i][j] = 0;
		}
	}
}

DirectedWeightedGraph::~DirectedWeightedGraph()
{
	for (int i = 0; i < n; i++)
	{
		delete[] this->adjMatrix[i];
	}
	delete[] this->adjMatrix;
}

DirectedWeightedGraph* DirectedWeightedGraph::CopyGraph()
{
	DirectedWeightedGraph* copy = new DirectedWeightedGraph(this->n);
	for (int u = 0; u < n; u++)
		for (int v = 0; v < n; v++)
			copy->adjMatrix[u][v] = this->adjMatrix[u][v];
	return copy;
}

bool DirectedWeightedGraph::IsAdjacent(int u, int v)
{
	return this->adjMatrix[u - 1][v - 1] != 0;
}

AdjList DirectedWeightedGraph::GetAdjList(int u)
{
	AdjList adjList;

	for (int i = 0; i < n; i++)
	{
		if (adjMatrix[u - 1][i] != 0)
		{
			adjList.Append(i + 1);
		}
	}

	return adjList;
}

void DirectedWeightedGraph::AddEdge(int u, int v, double c)
{
	this->adjMatrix[u - 1][v - 1] = c;
}

void DirectedWeightedGraph::RemoveEdge(int u, int v)
{
	this->adjMatrix[u - 1][v - 1] = 0;
}

void DirectedWeightedGraph::Print()
{
	for (int i = 0; i < n; i++)
	{
		cout << "|\t";
		for (int j = 0; j < n; j++)
		{
			cout << this->adjMatrix[i][j] << '\t';
		}
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
	return this->adjMatrix[u - 1][v - 1];
}


void DirectedWeightedGraph::AddWeight(int u, int v, double value)
{
	this->adjMatrix[u - 1][v - 1] += value;
}
