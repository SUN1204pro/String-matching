#include <iostream>
#include <vector>
#include <string>

using namespace std;


int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

void naive(const vector<vector<char>>& grid, const string& word,int& compare) {
    int rows = grid.size();
    int cols = grid[0].size();
    int len = word.size();

    vector<string> ans;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            for (int dir = 0; dir < 4; ++dir) {
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

                    string result = "(" + to_string(r) + ", " + to_string(c) + ") -> " +
                                              "(" + to_string(end_r) + ", " + to_string(end_c) + ")";
                    ans.push_back(result);
                }
            }
        }
    }

    cout << word << ": ";
    if (ans.empty()) {
        cout << "not found\n";
    } else {
        for (size_t i = 0; i < ans.size(); ++i) {
            cout << ans[i];
            if (i < ans.size() - 1) cout << "; ";
        }
        cout << ";\n";
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    int q;
    cin >> q;
    int compare = 0;
    while (q--) {
        string p;
        cin >> p;
        naive(grid, p,compare);
    }
    cout<<"Comparison: "<<compare;
    return 0;
}