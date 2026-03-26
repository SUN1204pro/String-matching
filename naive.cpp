#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Result {
    int r1, c1, r2, c2;
};

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

void naive(const vector<vector<char>> grid,string word) {
    int rows = grid.size();
    int cols = grid[0].size();
    int len = word.size();
    vector<Result> ans;
    int comparisons = 0;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            for (int dir = 0; dir < 4; ++dir) {
                int k;
                for (k = 0; k < len; ++k) {
                    int curr_r = r + dr[dir] * k;
                    int curr_c = c + dc[dir] * k;

                    if (curr_r < 0 || curr_r >= rows || curr_c < 0 || curr_c >= cols) break;

                    comparisons++; 
                    if (grid[curr_r][curr_c] != word[k]) break;
                }
                
                if (k == len) {
                    ans.push_back({r, c, r + dr[dir] * (len - 1), c + dc[dir] * (len - 1)});
                }
            }
        }
    }

    cout << word << ": ";
    if (ans.empty()) {
        cout << "not found" << endl;
    } else {
        for (size_t i = 0; i < ans.size(); ++i) {
            cout << "(" << ans[i].r1 << ", " << ans[i].c1 << ") -> "
                 << "(" << ans[i].r2 << ", " << ans[i].c2 << ")";
            if (i < ans.size() - 1) cout << "; ";
        }
        cout << ";" << '\n';
        cout << "Comparisons: " << comparisons << '\n';
    }
}

int main() {
    int n, m;
    cin>>n>>m;
    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    int q;
    cin >> q;
    while (q--) {
        string p;
        cin >> p;
        naive(grid, p);
    }
    return 0;
}