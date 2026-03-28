#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct TrieNode {
    int children[26];
    int fail;
    vector<int> matched_indices;

    TrieNode() {
        for (int i = 0; i < 26; i++) children[i] = -1;
        fail = -1;
    }
};

vector<TrieNode> trie;

void insert(const string& word, int word_index) {
    int curr = 0;
    for (char c : word) {
        int index = c - 'a';
        if (trie[curr].children[index] == -1) {
            trie[curr].children[index] = trie.size();
            trie.push_back(TrieNode());
        }
        curr = trie[curr].children[index];
    }
    trie[curr].matched_indices.push_back(word_index);
}

void build_failure_links() {
    queue<int> q;
    trie[0].fail = 0;

    for (int i = 0; i < 26; i++) {
        if (trie[0].children[i] != -1) {
            trie[trie[0].children[i]].fail = 0;
            q.push(trie[0].children[i]);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 0; i < 26; i++) {
            if (trie[u].children[i] != -1) {
                int v = trie[u].children[i];
                int f = trie[u].fail;

                while (f != 0 && trie[f].children[i] == -1) {
                    f = trie[f].fail;
                }

                if (trie[f].children[i] != -1) {
                    trie[v].fail = trie[f].children[i];
                } else {
                    trie[v].fail = 0;
                }

                for (int idx : trie[trie[v].fail].matched_indices) {
                    trie[v].matched_indices.push_back(idx);
                }

                q.push(v);
            }
        }
    }
}

void Aho_Corasick_SEARCH(const string& text, const vector<pair<int, int>>& coords, const vector<string>& queries, vector<string>& ans, int& comparison) {
    int curr = 0;
    for (int i = 0; i < text.length(); i++) {
        int index = text[i] - 'a';
        comparison++;

        while (curr != 0 && trie[curr].children[index] == -1) {
            curr = trie[curr].fail;
            comparison++;
        }

        if (trie[curr].children[index] != -1) {
            curr = trie[curr].children[index];
        }

        for (int word_idx : trie[curr].matched_indices) {
            int len = queries[word_idx].length();
            int start_idx = i - len + 1;
            int end_idx = i;

            string result = "(" + to_string(coords[start_idx].first) + ", " + to_string(coords[start_idx].second) + ") -> " +
                                      "(" + to_string(coords[end_idx].first) + ", " + to_string(coords[end_idx].second) + ")";

            if (!ans[word_idx].empty()) {
                ans[word_idx] += "; ";
            }
            ans[word_idx] += result;
        }
    }
}

void Aho_Corasick(const vector<vector<char>>& grid, const vector<string>& queries) {
    int rows = grid.size();
    if (rows == 0) return;
    int cols = grid[0].size();
    int comparison = 0;

    vector<string> ans(queries.size(), "");

    for (int r = 0; r < rows; r++) {
        string text_fwd = "", text_rev = "";
        vector<pair<int, int>> coords_fwd, coords_rev;

        for (int c = 0; c < cols; c++) {
            text_fwd += grid[r][c];
            coords_fwd.push_back({r, c});
            text_rev += grid[r][cols - 1 - c];
            coords_rev.push_back({r, cols - 1 - c});
        }
        Aho_Corasick_SEARCH(text_fwd, coords_fwd, queries, ans, comparison);
        Aho_Corasick_SEARCH(text_rev, coords_rev, queries, ans, comparison);
    }

    for (int c = 0; c < cols; c++) {
        string text_fwd = "", text_rev = "";
        vector<pair<int, int>> coords_fwd, coords_rev;

        for (int r = 0; r < rows; r++) {
            text_fwd += grid[r][c];
            coords_fwd.push_back({r, c});
            text_rev += grid[rows - 1 - r][c];
            coords_rev.push_back({rows - 1 - r, c});
        }
        Aho_Corasick_SEARCH(text_fwd, coords_fwd, queries, ans, comparison);
        Aho_Corasick_SEARCH(text_rev, coords_rev, queries, ans, comparison);
    }

    for (size_t i = 0; i < queries.size(); i++) {
        cout << queries[i] << ": ";
        if (ans[i].empty()) {
            cout << "not found\n";
        } else {
            cout << ans[i] << ";\n";
        }
    }
    cout << "Comparisons: " << comparison << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

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

    trie.push_back(TrieNode());

    vector<string> queries(q);
    for(int i = 0; i < q; i++) {
        cin >> queries[i];
        insert(queries[i], i);
    }

    build_failure_links();

    Aho_Corasick(grid, queries);

    return 0;
}