#include "FordFulkersonHandler.h"
#include "Utility.h"

FordFulkersonHandler::~FordFulkersonHandler()
{
	delete this->MinCut;
}

//uses BFS to find a path from s to t, indicated in parent[] if found
bool FordFulkersonHandler::FindPath(DirectedWeightedGraph* graph, int s, int t, int parent[])
{
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
			if (!visited[v] && graph->GetCapacity(u, v) > 0)
			{
				q.Enqueue(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
		if (visited[t])
		{
			return true;
		}
	}

	return false;
}

//uses DFS to find reachable nodes, indicated in visited vector
void FordFulkersonHandler::TraverseGraph(DirectedWeightedGraph* graph, int s, vector<bool>* visited)
{
	visited->at(s) = true;
	for (int i = 1; i <= graph->GetNumberOfVertices(); i++)
	{
		if (graph->GetCapacity(s, i) && !(*visited)[i])
		{
			this->TraverseGraph(graph, i, visited);
		}
	}
}

//initiate incresable flow: s's neighbour v with C(s,v) and the rest -infinity
//parent = -1: represents no parent. increasableFlow[v] = -1: represents -infinity
void FordFulkersonHandler::InitFlow(DirectedWeightedGraph*& graph, int s, int parent[], double flow[])
{
	int n = graph->GetNumberOfVertices();
	for (int i = 1; i <= n; i++)
	{
		double Csi = graph->GetCapacity(s, i);
		if (Csi > 0)
		{
			flow[i] = Csi;
			parent[i] = s;
		}
		else
		{
			flow[i] = -1;
			parent[i] = -1;
		}
	}
	flow[s] = 0;
}

//uses Dijkstra to return max flow on a path from s to t, and returns the path in parent[]
double FordFulkersonHandler::FindMaxFlowOnPath(DirectedWeightedGraph* graph, int s, int t, int parent[])
{
	int u, v;
	int n = graph->GetNumberOfVertices();
	double* flow = new double[n + 1];	//flow[v] contains increasable flow value to v
	this->InitFlow(graph, s, parent, flow);
	MaxPriorityQueue* Q = new MaxPriorityQueue(flow, n);
	while (!Q->IsEmpty())
	{
		u = Q->DeleteMax();
		for (v = 1; v <= n; v++)
		{
			double Cuv = graph->GetCapacity(u, v);
			if (Cuv > 0)	//if (u,v) edge in graph
			{
				if (flow[v] < Cuv && flow[v] < flow[u])	//able to increase flow from u to v if u has more flow and C(u,v) enables it
				{
					if (Cuv < flow[u])	//C(u,v) is the max to flow
					{
						flow[v] = Cuv;
					}
					else				//flow[u] is the max to flow
					{
						flow[v] = flow[u];
					}
					parent[v] = u;
					Q->IncreaseValue(v, flow[v]);
				}
			}
		}
	}
	double res = flow[t];
	delete[] flow;
	delete Q;

	return res;
}

void FordFulkersonHandler::UpdateFlowOnPath(DirectedWeightedGraph* graph, int s, int t, int parent[], double flowOnPath)
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
	double flowOnPath = 0;

	switch (method)
	{
	case EDMONDS_KARP:
		while (this->FindPath(residualGraph, s, t, parent))
		{
			(*iterations)++;
			flowOnPath = DBL_MAX;
			for (v = t; v != s; v = parent[v])
			{
				u = parent[v];
				flowOnPath = min(flowOnPath, residualGraph->GetCapacity(u, v));
			}

			//Update the residual capacity, as well as on the reverse path
			this->UpdateFlowOnPath(residualGraph, s, t, parent, flowOnPath);

			//Update the flow on the path to the overall graph flow
			maxFlow += flowOnPath;
		}
		break;
	case DIJKSTRA:
		flowOnPath = this->FindMaxFlowOnPath(residualGraph, s, t, parent);
		while (flowOnPath > 0)
		{
			(*iterations)++;

			//Update the residual capacity, as well as on the reverse path
			this->UpdateFlowOnPath(residualGraph, s, t, parent, flowOnPath);

			//Update the flow on the path to the overall graph flow
			maxFlow += flowOnPath;
			flowOnPath = this->FindMaxFlowOnPath(residualGraph, s, t, parent);
		}
		break;
	}

	//Find min cut after find residual graph and return max flow
	this->CalculateMinCut(residualGraph, s);
	delete residualGraph; // dynamically allocated by copyGraph()
	delete[] parent; //dynamically allocated
	return maxFlow;
}

vector<vector<int>> FordFulkersonHandler::GetMinCut()
{
	return *this->MinCut;
}

void FordFulkersonHandler::CalculateMinCut(DirectedWeightedGraph* residualGraph, int s)
{
	int n = residualGraph->GetNumberOfVertices();
	vector<bool>* visited = new vector<bool>(n + 1);

	(*this->MinCut)[S].clear();
	(*this->MinCut)[T].clear();
	this->TraverseGraph(residualGraph, s, visited);
	for (int i = 1; i <= n; i++)
	{
		if ((*visited)[i])
		{
			(*this->MinCut)[S].push_back(i);
		}
		else
		{
			(*this->MinCut)[T].push_back(i);
		}
	}

	// dinamically allocated
	delete visited;
}