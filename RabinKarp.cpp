#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include "Function.h"

using namespace std;

const long long base = 311;
const long long MOD = 1e9 + 2277;

long long binpow(long long a, long long b) {
	long long ans = 1;
	while (b) {
		if (b & 1) ans = ans * a % MOD;
		a = a * a % MOD;
		b >>= 1;
	}
	return ans;
}

void RabinKarp(string str, string pattern, long long& count_comparisons, int row, int col, bool isHorizontal, string& pos) {
	int n = str.length(), m = pattern.length();
	if (n < m) return;

	long long hashpat = 0, hashstr = 0;
	for (int i = 0; i < m; ++i) {
		hashpat = (hashpat * base + pattern[i] - 'a' + 1) % MOD;
		hashstr = (hashstr * base + str[i] - 'a' + 1) % MOD;
	}

	long long exp = binpow(base, m - 1);
	for (int i = 0; i <= n - m; ++i) {
		++count_comparisons;
		if (hashstr == hashpat) {
			if (isHorizontal) {
				pos += '(' + to_string(row) + ", " + to_string(col + i) + ") -> (" + to_string(row) + ", " + to_string(col + i + m - 1) + "); ";
			}
			else {
				pos += '(' + to_string(row + i) + ", " + to_string(col) + ") -> (" + to_string(row + i + m - 1) + ", " + to_string(col) + "); ";
			}
		}

		if (i < n - m) {
			hashstr = ((hashstr - exp * (str[i] - 'a' + 1) % MOD + MOD) * base % MOD + str[i + m] - 'a' + 1) % MOD;
		}
	}
}

void RabinKarp2D(int R, int C, const vector<vector<char>>& grid, const vector<string>& pattern, vector<string>& pos, long long& total_comparisons) {
	for (int index = 0; index < pattern.size(); ++index) {
		string pat = pattern[index];
		string strPos = "";

		// Horizontal
		for (int i = 0; i < R; ++i) {
			string str = "";
			for (int j = 0; j < C; ++j) {
				str += grid[i][j];
			}
			RabinKarp(str, pat, total_comparisons, i, 0, true, strPos);
		}

		// Vertical
		for (int i = 0; i < C; ++i) {
			string str = "";
			for (int j = 0; j < R; ++j) {
				str += grid[j][i];
			}
			RabinKarp(str, pat, total_comparisons, 0, i, false, strPos);
		}

		if (strPos == "") strPos = "not found";
		pos.push_back(strPos);
	}
}