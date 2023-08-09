#include "FordFulkersonHandler.h"

FordFulkersonHandler::~FordFulkersonHandler()
{
	delete MinCut;
}

bool FordFulkersonHandler::BFS(DirectedWeightedGraph* graph, int s, int t, int parent[])
{
	//graph is the Residual Graph.
	//Start visited array(vector) with n elements, init all with 0(false)
	const int n = graph->GetNumberOfVertices();
	vector<bool> visited(n + 1, 0);

	//Start empty Queue and push S
	Queue q;
	q.makeEmpty();
	q.Enqueue(s);

	//Prequisites, set S as visited and -1 at parent array.
	visited[s] = true;
	parent[s] = -1;

	while (!q.isEmpty())
	{
		int u = q.Dequeue();

		for (int v = 1; v <= n; v++)
		{
			if (visited[v] == false && graph->GetCapacity(u, v) > 0)
			{
				q.Enqueue(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}

	// If we reached T(The sink) for S(the source) we will return true
	return (visited[t] == true);
}

void FordFulkersonHandler::DFS(DirectedWeightedGraph* graph, int s, vector<bool>* visited)
{
	visited->at(s) = true;
	for (int i = 1; i <= graph->GetNumberOfVertices(); i++)
		if (graph->GetCapacity(s, i) && !(*visited)[i])
			DFS(graph, i, visited);
}

void FordFulkersonHandler::INIT(DirectedWeightedGraph*& graph, int s, int parent[], double* d)
{
	//initiate also s's neighbour v with C(s,v)
	//parent = -1: represents no parent. d[v] = -1: represents -infinity
	int n = graph->GetNumberOfVertices();
	for (int i = 1; i <= n; i++)
	{
		double Csi = graph->GetCapacity(s, i);
		if (Csi > 0)
		{
			d[i] = Csi;
			parent[i] = s;
		}
		else
		{
			d[i] = -1;
			parent[i] = -1;
		}
	}
	d[s] = 0;
}

double FordFulkersonHandler::DIJKSTRA(DirectedWeightedGraph* graph, int s, int t, int parent[])
{
	//returns the flow to improve, and returns the path in parent[]
	int u, v;
	int n = graph->GetNumberOfVertices();
	double* d = new double[n + 1];	//d[v] contains increasable flow value in v
	MaxPriorityQueue Q;
	INIT(graph, s, parent, d);
	Q.Build(d, n);
	while (!Q.IsEmpty())
	{
		u = Q.DeleteMax();
		for (v = 1; v <= n; v++)
		{
			double Cuv = graph->GetCapacity(u, v);
			if (Cuv > 0)	//if (u,v) edge in graph
			{
				if (d[v] < Cuv && d[v] < d[u])	//ability to flow depands both on d[u] and on C(u,v)
				{
					if (Cuv < d[u])	//C(u,v) is the max to flow
						d[v] = Cuv;
					else			//d[u] is the max to flow
						d[v] = d[u];
					parent[v] = u;
					Q.IncreaseKey(v, d[v]);
				}
			}
		}
	}
	double res = d[t];
	delete d; // dynamically alocated
	return res;
}

void FordFulkersonHandler::UpdatePath(DirectedWeightedGraph* graph, int s, int t, int parent[], double flowOnPath)
{
	int u, v;
	//Update the residual capacity, as well as on the reverse path
	for (v = t; v != s; v = parent[v])
	{
		u = parent[v];
		graph->AddWeight(v, u, flowOnPath);
		graph->AddWeight(u, v, -flowOnPath);
	}
}

double FordFulkersonHandler::FordFulkersonAlg(DirectedWeightedGraph* graph, int s, int t, short method, int* iterations)
{
	//We pass graph by value since we will work on the residual graph from now, not on the original.
	int u, v;
	int n = graph->GetNumberOfVertices();
	*iterations = 0;
	DirectedWeightedGraph* residualGraph = graph->CopyGraph();

	int* parent = new int[n + 1];

	double maxFlow = 0;
	double flowOnPath;

	switch (method)
	{
	case _BFS:
		while (BFS(residualGraph, s, t, parent))
		{
			(*iterations)++;
			flowOnPath = DBL_MAX;
			for (v = t; v != s; v = parent[v])
			{
				u = parent[v];
				flowOnPath = min(flowOnPath, residualGraph->GetCapacity(u, v));
			}
			//Update the residual capacity, as well as on the reverse path
			UpdatePath(residualGraph, s, t, parent, flowOnPath);

			//Update the flow on the path to the overall graph flow
			maxFlow += flowOnPath;
		}
		break;
	case _GREEDY:
		flowOnPath = DIJKSTRA(residualGraph, s, t, parent);
		while (flowOnPath > 0)
		{
			(*iterations)++;

			//Update the residual capacity, as well as on the reverse path
			UpdatePath(residualGraph, s, t, parent, flowOnPath);

			//Update the flow on the path to the overall graph flow
			maxFlow += flowOnPath;
			flowOnPath = DIJKSTRA(residualGraph, s, t, parent);
		}
		break;
	}
	//Find min cut after find residual graph and return max flow
	FindMinCut(residualGraph, s);
	delete residualGraph; // dynamically allocated by copyGraph()
	delete parent; //dynamically allocated
	return maxFlow;
}

void FordFulkersonHandler::PrintMinCut()
{
	int sizeOfS = (*MinCut)[S].size();
	int sizeOfT = (*MinCut)[T].size();

	cout << "Min cut: " <<
		"S = ";
	for (int i = 0; i < sizeOfS; i++)
	{
		int vortice = (*MinCut)[S][i];
		if (i == sizeOfS - 1)
			cout << vortice << ". ";
		else
			cout << vortice << ", ";
	}

	cout << "T = ";
	for (int i = 0; i < sizeOfT; i++)
	{
		int vortice = (*MinCut)[T][i];
		if (i == sizeOfT - 1)
			cout << vortice << "\n";
		else
			cout << vortice << ", ";
	}

}

void FordFulkersonHandler::FindMinCut(DirectedWeightedGraph* resGraph, int s)
{
	(*MinCut)[S].clear();
	(*MinCut)[T].clear();
	int n = resGraph->GetNumberOfVertices();
	vector<bool>* visited = new vector<bool>(n + 1);
	DFS(resGraph, s, visited);
	for (int i = 1; i <= n; i++)
	{
		if ((*visited)[i])
		{
			(*MinCut)[S].push_back(i);
		}
		else
		{
			(*MinCut)[T].push_back(i);
		}
	}
	// dinamically allocated
	delete visited;

	// MinCut = minCut;
}