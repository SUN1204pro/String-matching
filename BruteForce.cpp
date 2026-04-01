#include <iostream>
#include <vector>
#include <string>
#include "Function.h"

using namespace std;

int dr[] = { 0, 1 };
int dc[] = { 1, 0 };

void naive(const vector<vector<char>>& grid, const vector<string>& pattern, vector<string>& ans, long long& compare) {
    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < pattern.size(); ++i) {
        string word = pattern[i];
        int len = word.size();
        string result = "";

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                for (int dir = 0; dir < 2; ++dir) {
                    int k;
                    for (k = 0; k < len; ++k) {
                        int curr_r = r + dr[dir] * k;
                        int curr_c = c + dc[dir] * k;

                        if (curr_r < 0 || curr_r >= rows || curr_c < 0 || curr_c >= cols) break;

                        compare++;
                        if (grid[curr_r][curr_c] != word[k]) break;
                    }

                    if (k == len) {
                        int end_r = r + dr[dir] * (len - 1);
                        int end_c = c + dc[dir] * (len - 1);

                        result += "(" + to_string(r) + ", " + to_string(c) + ") -> " +
                            "(" + to_string(end_r) + ", " + to_string(end_c) + "); ";
                    }
                }
            }
        }
        ans.push_back(result);
    }
}