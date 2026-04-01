#pragma once
#include <string>
#include <vector>

using namespace std;

// Brute force
void naive(const vector<vector<char>>& grid, const vector<string>& pattern, vector<string>& ans, long long& compare);


// Rabin-Karp
long long binpow(long long a, long long b);
void RabinKarp(string str, string pattern, long long& count_comparisons, int row, int col, bool isHorizontal, string& pos);
void RabinKarp2D(int R, int C, vector<vector<char>> grid, vector<string> pattern, vector<string>& pos, long long& total_comparisons);

// KMP
vector<int> computePrefixFunction(const string& P);
void KMP(const string& str, const string& pattern, long long& total_comparisons, int row, int col, bool isHorizontal, string& strPos);
void KMP2D(int R, int C, vector<vector<char>> grid, vector<string> pattern, vector<string>& pos, long long& total_comparisons);

// Boyer-Moore
string formatPos(int r1, int c1, int r2, int c2);
void BoyerMoore(const vector<vector<char>>& grid, const vector<string>& patterns, vector<string>& pos, long long& count);

// Aho-Corasick
void insert(const string& word, int word_index);
void build_failure_links();
void Aho_Corasick_SEARCH(const string& text, const vector<pair<int, int>>& coords, const vector<string>& queries, vector<string>& ans, long long& comparison);
void Aho_Corasick(const vector<vector<char>>& grid, const vector<string>& queries, vector<string>& ans, long long& comparison);
void Aho_Corasick_2D(vector<vector<char>> grid, vector<string> pattern, vector<string>& pos, long long& total_comparisons);