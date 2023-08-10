#pragma once

#include <string>
#include <vector>
#include <sstream>

using namespace std;

namespace input_helper
{
	void quitWithInvalidInput(const string msg = "");
	bool isDigits(const string& str);
	void validateInputLineAndCountEdges(vector<string> line, int* edgesCount);
	void validateInput(vector<vector<string>> input);
	template <typename Out>
	void parse(const string&, char, Out);
	vector<string> getParsed(const string&, char);
	int getN(vector<vector<string>> input);
	int getM(vector<vector<string>> input);
	int getS(vector<vector<string>> input);
	int getT(vector<vector<string>> input);
}