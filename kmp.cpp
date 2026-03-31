#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> computePrefixFunction(const string& P) {
    int m = P.length();
    vector<int> pi(m, 0);
    int k = 0;
    
    for (int q = 1; q < m; ++q) {
        while (k > 0 && P[k] != P[q])
            k = pi[k - 1];
        if (P[k] == P[q])
            k++;
        pi[q] = k;
    }
    return pi;
}

void KMP(const string& str, const string& pattern, int& total_comparisons, int row, int col, bool isHorizontal, string& strPos) {
    int n = str.length();
    int m = pattern.length();
    
    if (m == 0 || n == 0) return;

    vector<int> pi = computePrefixFunction(pattern);
    int q = 0;

    for (int i = 0; i < n; ++i) {
        while (q > 0) {
            total_comparisons++;
            if (pattern[q] == str[i]) break;
            q = pi[q - 1];
        }

        if (q == 0) {
            total_comparisons++;
            if (pattern[0] == str[i])
                q++;
        } else
            q++;

        if (q == m) {
            int match_start_index = i - m + 1; 
            int match_end_index = i; 

            if (isHorizontal)
                strPos += "(" + to_string(row) + ", " + to_string(col + match_start_index) + ") -> (" + 
                          to_string(row) + ", " + to_string(col + match_end_index) + "); ";
            else
                strPos += "(" + to_string(row + match_start_index) + ", " + to_string(col) + ") -> (" + 
                          to_string(row + match_end_index) + ", " + to_string(col) + "); ";
            
            q = pi[q - 1];
        }
    }
}