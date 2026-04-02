#include <vector>
#include <string>
#include <algorithm>
#include "Function.h"

using namespace std;

string formatPos(int r1, int c1, int r2, int c2) {
    return "(" + to_string(r1) + ", " + to_string(c1) + ") -> (" + to_string(r2) + ", " + to_string(c2) + ")";
}


void BoyerMoore(const vector<vector<char>>& grid, const vector<string>& patterns, vector<string>& pos, long long& count) {
    int R = grid.size(), C = grid[0].size();
    for (const string& word : patterns) {
        vector<string> matches; int m = word.length();
        int badchar[256]; for (int i = 0; i < 256; i++) badchar[i] = -1;
        for (int i = 0; i < m; i++) badchar[(unsigned char)word[i]] = i;

        auto search = [&](const string& text, int line_idx, bool horiz) {
            int s = 0, n = text.length();
            while (s <= (n - m)) {
                int j = m - 1;
                while (j >= 0) { count++; if (word[j] == text[s + j]) j--; else break; }
                if (j < 0) {
                    if (horiz) matches.push_back(formatPos(line_idx, s, line_idx, s + m - 1));
                    else matches.push_back(formatPos(s, line_idx, s + m - 1, line_idx));
                    s += (s + m < n) ? m - badchar[(unsigned char)text[s + m]] : 1;
                }
                else s += max(1, j - badchar[(unsigned char)text[s + j]]);
            }
            };

        for (int r = 0; r < R; r++) { string row = ""; for (char ch : grid[r]) row += ch; search(row, r, true); }
        for (int c = 0; c < C; c++) { string col = ""; for (int r = 0; r < R; r++) col += grid[r][c]; search(col, c, false); }

        if (matches.empty()) pos.push_back("not found");
        else { string res = ""; for (size_t i = 0; i < matches.size(); i++) res += matches[i] + (i == matches.size() - 1 ? "" : "; "); pos.push_back(res); }
    }
}