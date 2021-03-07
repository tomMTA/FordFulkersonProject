#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <fstream>
#include <stdlib.h>
#include"FordFulkerson.h"

using namespace std;

void quitProgram(const std::string MSG = "");
void ValidateInput(std::vector<std::string>, int*);
template <typename Out>
void split(const std::string&, char, Out);
std::vector<std::string> split(const std::string&, char);
bool is_digits(const std::string& str);

int main(int argc, char* argv[])
{
	DirectedWeightedGraph* graph = new DirectedWeightedGraph();
	vector<std::vector<std::string>> textFromFileSplitted;
	int n, m, t, s;
	int iterationsBFS, iterationsGreedy;
	int* edgesCount = new int();

	//Start from 0 edges
	*(edgesCount) = 0;
	//Read file
	std::ifstream input(argv[1]);
	//Process line by line and count how many edges are present
	for (std::string line; getline(input, line); )
	{
		//Split contents by spaces, will ignore all whitespaces in a line.
		std::vector<std::string> splittedString = split(line, ' ');
		// If the line is an empty line, skip it
		if (splittedString.size() == 0)
			continue;
		ValidateInput(splittedString, edgesCount);
		textFromFileSplitted.push_back(splittedString);
	}

	// is at least n,m,s,t in text
	if (textFromFileSplitted.size() < 4)
		quitProgram("Less than 4 lines.");

	// get n and m
	n = std::stoi(textFromFileSplitted[0][0]);
	m = std::stoi(textFromFileSplitted[1][0]);

	// get s and t
	s = std::stoi(textFromFileSplitted[2][0]);
	t = std::stoi(textFromFileSplitted[3][0]);

	if (s == t)
		quitProgram("s and t canot be the same vertex.");
	if (*(edgesCount) != m)
		quitProgram("Number of edges not as specified.");

	//Make enpty graph
	graph->MakeEmptyGraph(n);

	//Iterate on rows and build the graph
	for (int i = 4; i <= m + 3; i++)
	{
		int x, y;
		double capacity;
		std::vector<std::string> row = textFromFileSplitted[i];
		x = std::stoi(row[0]);
		y = std::stoi(row[1]);
		capacity = std::stod(row[2]);

		// check if (x,y) already exists in graph
		if (graph->IsAdjacent(x, y))
			quitProgram("Parallel edges are not allowed.");
		graph->AddEdge(x, y, capacity);
	}

	FordFulkerson handler;

	double maxFlow = handler.FordFulkersonAlg(graph, s, t, _BFS, &iterationsBFS);
	cout << "BFS Method:\n"
		<< "Max flow = "
		<< maxFlow
		<< "\n";
	handler.PrintMinCut();
	cout << "Number of iterations: "
		<< iterationsBFS
		<< "\n";

	maxFlow = handler.FordFulkersonAlg(graph, s, t, _GREEDY, &iterationsGreedy);
	cout << "Greedy Method:\n"
		<< "Max flow = "
		<< maxFlow
		<< "\n";
	handler.PrintMinCut();
	cout << "Number of iterations: "
		<< iterationsGreedy
		<< "\n";

	//dynamically allocated
	delete edgesCount;
	delete graph;
	system("pause");
}

void ValidateInput(std::vector<std::string> line, int* edgesCount)
{
	static bool isNSet = false;
	static int singleCharLines = 0;
	static int n = 0;
	int x, y;
	double capacity;

	for (auto lineContent : line)
	{
		//Run on each string in the line and check if it they are only digits
		if (!is_digits(lineContent))
			quitProgram("Only numbers allowed.");
	}

	if (line.size() == 1 && singleCharLines < 4)
	{
		singleCharLines++;
		if (std::stoi(line[0]) <= 0)
			quitProgram("Out of valid range.");
		if (!isNSet)
		{
			if (std::stoi(line[0]) == 1)
				quitProgram("There has to be at least 2 nodes in a flow network");
			n = std::stoi(line[0]);
			isNSet = true;
		}
	}
	else if (line.size() == 3 && singleCharLines == 4)
	{
		x = std::stoi(line[0]);
		y = std::stoi(line[1]);
		capacity = std::stod(line[2]);

		// check negative capacity
		if (capacity <= 0 || x > n || x < 1 || y > n || x < 1)
		{
			quitProgram("Check edges or capacity value.");
		}

		//check for loops
		if (x == y)
			quitProgram("No loops allowed.");

		(*edgesCount)++;
	}
	else
		quitProgram("Invalid Amount of parameters in line");

}

void quitProgram(const std::string MSG)
{
	cout << "Invalid Input. " << MSG << endl;
	system("pause");
	exit(1);
}

template <typename Out>
void split(const std::string& s, char delim, Out result) {
	std::istringstream iss(s);
	std::string item;
	while (std::getline(iss, item, delim)) {
		//Check if string is a whitespace, if it is, ignore whitespaces
		if (std::all_of(item.begin(), item.end(), isspace))
			continue;
		*result++ = item;
	}
}

std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

bool is_digits(const std::string& str)
{
	return str.find_first_not_of("0123456789.") == std::string::npos;
}