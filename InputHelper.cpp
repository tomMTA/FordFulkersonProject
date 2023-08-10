#include <string>
#include <vector>
#include <algorithm>
#include "InputHelper.h"
#include "Utility.h"

using namespace utility;

void input_helper::quitWithInvalidInput(const string msg)
{
	quitWithMsg("Invalid input. " + msg);
}

bool input_helper::isDigits(const string& str)
{
	return str.find_first_not_of("0123456789.") == string::npos;
}


void input_helper::validateInputLineAndCountEdges(vector<string> line, int* edgesCount)
{
	static bool isNSet = false;
	static int singleCharLines = 0;
	static int n = 0;
	int u, v;
	double capacity;

	for (auto lineContent : line)
	{
		//Run on each string in the line and check if it they are only digits
		if (!isDigits(lineContent))
		{
			quitWithInvalidInput("Only numbers allowed.");
		}
	}

	if (line.size() == 1 && singleCharLines < 4)
	{
		singleCharLines++;
		if (stoi(line[0]) <= 0)
		{
			quitWithInvalidInput("Out of valid range.");
		}
		if (!isNSet)
		{
			if (stoi(line[0]) == 1)
			{
				quitWithInvalidInput("There has to be at least 2 nodes in a flow network");
			}
			n = stoi(line[0]);
			isNSet = true;
		}
	}
	else if (line.size() == 3 && singleCharLines == 4)
	{
		u = stoi(line[0]);
		v = stoi(line[1]);
		capacity = stod(line[2]);

		// check negative capacity
		if (capacity <= 0 || u > n || u < 1 || v > n || u < 1)
		{
			quitWithInvalidInput("Check edges or capacity value.");
		}

		//check for loops
		if (u == v)
		{
			quitWithInvalidInput("No loops allowed.");
		}

		(*edgesCount)++;
	}
	else
	{
		quitWithInvalidInput("Invalid Amount of parameters in line");
	}
}

void input_helper::validateInput(vector<vector<string>> input)
{
	if (input.size() < 4)
	{
		quitWithInvalidInput("Less than 4 lines. At least n,m,s,t should be provided");
	}

	int* edgesCount = new int();
	for (auto line : input)
	{
		validateInputLineAndCountEdges(line, edgesCount);
	}

	int n = getN(input);
	int m = getM(input);
	int s = getS(input);
	int t = getT(input);

	if (s == t)
	{
		quitWithInvalidInput("s and t canot be the same vertex.");
	}
	if (*edgesCount != m)
	{
		quitWithInvalidInput("Number of edges not as specified.");
	}
}

template <typename Out>
void input_helper::parse(const string& s, char delim, Out result) {
	istringstream iss(s);
	string item;
	while (getline(iss, item, delim))
	{
		//Check if string is a whitespace, if it is, ignore whitespaces
		if (all_of(item.begin(), item.end(), isspace))
		{
			continue;
		}
		*result++ = item;
	}
}

vector<string> input_helper::getParsed(const string& s, char delim) {
	vector<string> elems;
	parse(s, delim, back_inserter(elems));
	return elems;
}

int input_helper::getN(vector<vector<string>> input)
{
	return stoi(input[0][0]);
}

int input_helper::getM(vector<vector<string>> input)
{
	return stoi(input[1][0]);
}

int input_helper::getS(vector<vector<string>> input)
{
	return stoi(input[2][0]);
}

int input_helper::getT(vector<vector<string>> input)
{
	return stoi(input[3][0]);
}
