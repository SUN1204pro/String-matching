#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <chrono>
#include "Function.h"

using namespace std;

void readFile(string filename, int& row, int& col, vector<vector<char>>& grid, vector<string>& pattern) {
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open()) {
		cout << "Can not open file " << filename << endl;
		return;
	}

	fin >> row >> col;
	grid.resize(row);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			char ch; fin >> ch;
			grid[i].push_back(ch);
		}
	}
	int k; fin >> k;
	while (k--) {
		string str = ""; fin >> str;
		pattern.push_back(str);
	}

	fin.close();
}

void runAlgorithm(string algorithm, int R, int C, vector<vector<char>> grid, vector<string> pattern, vector<string>& pos, long long& total_comparisons, double& executionTime) {
	if (algorithm == "bf") {
		auto start_time = chrono::high_resolution_clock::now();
		naive(grid, pattern, pos, total_comparisons);
		auto end_time = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> time_span = end_time - start_time;
		executionTime = time_span.count();
	}
	
	if (algorithm == "rk") {
		auto start_time = chrono::high_resolution_clock::now();
		RabinKarp2D(R, C, grid, pattern, pos, total_comparisons);
		auto end_time = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> time_span = end_time - start_time;
		executionTime = time_span.count();
	}

	if (algorithm == "kmp") {
		auto start_time = chrono::high_resolution_clock::now();
		KMP2D(R, C, grid, pattern, pos, total_comparisons);
		auto end_time = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> time_span = end_time - start_time;
		executionTime = time_span.count();
	}

	if (algorithm == "bm") {
		auto start_time = chrono::high_resolution_clock::now();
		BoyerMoore(grid, pattern, pos, total_comparisons);
		auto end_time = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> time_span = end_time - start_time;
		executionTime = time_span.count();
	}

	if (algorithm == "ac") {
		auto start_time = chrono::high_resolution_clock::now();
		Aho_Corasick_2D(grid, pattern, pos, total_comparisons);
		auto end_time = chrono::high_resolution_clock::now();
		chrono::duration<double, milli> time_span = end_time - start_time;
		executionTime = time_span.count();
	}
}

void writeFile(string filename, string algorithm, vector<string> pattern, vector<string> pos, long long total_comparisons, double executionTime) {
	ofstream fout;
	fout.open(filename);
	if (!fout.is_open()) {
		cout << "Can not write file " << filename << endl;
		return;
	}

	// In theo dinh dang
	for (int i = 0; i < pattern.size(); ++i) {
		fout << pattern[i] << ": " << pos[i] << endl;
	}

	fout << endl;
	fout << "--------------------------------" << endl;
	fout << "Algorithm: " << algorithm << endl;
	fout << "Comparisons: " << total_comparisons << endl;
	fout << "Execution Time: " << fixed << setprecision(2) << executionTime << " ms" << endl;

	fout.close();
}

int main(int argc, char* argv[])
{
	if (argc < 7) {
		cout << "Error";
		return 0;
	}
	

	string inputFile = argv[4];
	int R = 0, C = 0;
	vector<vector<char>> grid;
	vector<string> pattern;
	readFile(inputFile, R, C, grid, pattern);
	if (R == 0) {
		cout << "ERROR";
		return 0;
	}


	string algorithm = argv[2];
	vector<string> pos;
	long long total_comparisons = 0;
	double executionTime = 0;
	runAlgorithm(algorithm, R, C, grid, pattern, pos, total_comparisons, executionTime);


	string outputFile = argv[6];
	string algo = "";
	if (algorithm == "bf") algo = "Brute-Force";
	if (algorithm == "rk") algo = "Rabin-Karp";
	if (algorithm == "kmp") algo = "KMP";
	if (algorithm == "bm") algo = "Boyer-Moore";
	if (algorithm == "ac") algo = "Aho-Corasick";
	writeFile(outputFile, algo, pattern, pos, total_comparisons, executionTime);

	

	return 0;
}
