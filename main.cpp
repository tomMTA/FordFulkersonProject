#include <string>
#include <vector>
#include <fstream>
#include "FordFulkersonHandler.h"
#include "MaxPriorityQueue.h"
#include "InputHelper.h"
#include "Utility.h"

using namespace std;
using namespace input_helper;
using namespace utility;

int main(int argc, char* argv[])
{
	DirectedWeightedGraph* graph;
	vector<vector<string>> textFromFileParsed;
	int n, m, t, s;
	int iterationsBFS, iterationsGreedy;
	int* edgesCount = new int();

	//Start from 0 edges
	*(edgesCount) = 0;
	//Read file...
	ifstream input(argv[1]);
	//ifstream input("C:\\Users\\Tom\Desktop\\VS_Projects\\FordFulkersonProject\\inputs\\input1.txt");
	//Process line by line and count how many edges are present
	for (string line; getline(input, line); )
	{
		//Split contents by spaces, will ignore all whitespaces in a line.
		vector<string> parsedLine = getParsed(line, ' ');
		// If the line is an empty line, skip it
		if (parsedLine.size() == 0)
		{
			continue;
		}
		textFromFileParsed.push_back(parsedLine);
	}

	validateInput(textFromFileParsed);

	n = getN(textFromFileParsed);
	m = getM(textFromFileParsed);
	s = getS(textFromFileParsed);
	t = getT(textFromFileParsed);

	//Make empty graph
	graph = new DirectedWeightedGraph(n);

	//Iterate on rows and build the graph
	for (int i = 4; i <= m + 3; i++)
	{
		int u, v;
		double capacity;
		vector<string> row = textFromFileParsed[i];
		u = stoi(row[0]);
		v = stoi(row[1]);
		capacity = stod(row[2]);

		// check if (u,v) already exists in graph
		if (graph->IsAdjacent(u, v))
		{
			quitWithInvalidInput("Parallel edges are not allowed.");
		}
		graph->AddEdge(u, v, capacity);
	}

	FordFulkersonHandler handler;

	double maxFlow = handler.FordFulkersonAlg(graph, s, t, EDMONDS_KARP, &iterationsBFS);
	printResult("Edmonds–Karp", maxFlow, handler.GetMinCut(), iterationsBFS);

	maxFlow = handler.FordFulkersonAlg(graph, s, t, DIJKSTRA, &iterationsGreedy);
	printResult("Dijkstra", maxFlow, handler.GetMinCut(), iterationsGreedy);

	//dynamically allocated
	delete edgesCount;
	delete graph;
	system("pause");
}