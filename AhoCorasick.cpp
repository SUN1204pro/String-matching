#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "Function.h"
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
                }
                else {
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

void Aho_Corasick_SEARCH(const string& text, const vector<pair<int, int>>& coords, const vector<string>& queries, vector<string>& ans, long long& comparison) {
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
                "(" + to_string(coords[end_idx].first) + ", " + to_string(coords[end_idx].second) + "); ";

            ans[word_idx] += result;
        }
    }
}

void Aho_Corasick(const vector<vector<char>>& grid, const vector<string>& queries, vector<string>& ans, long long& comparison) {
    int rows = grid.size();
    if (rows == 0) return;
    int cols = grid[0].size();
    comparison = 0;

    ans.resize(queries.size(), "");

    for (int r = 0; r < rows; r++) {
        string text_fwd = "";
        vector<pair<int, int>> coords_fwd;

        for (int c = 0; c < cols; c++) {
            text_fwd += grid[r][c];
            coords_fwd.push_back({ r, c });
        }
        Aho_Corasick_SEARCH(text_fwd, coords_fwd, queries, ans, comparison);
    }

    for (int c = 0; c < cols; c++) {
        string text_fwd = "";
        vector<pair<int, int>> coords_fwd;

        for (int r = 0; r < rows; r++) {
            text_fwd += grid[r][c];
            coords_fwd.push_back({ r, c });
        }
        Aho_Corasick_SEARCH(text_fwd, coords_fwd, queries, ans, comparison);
    }

    for (int i = 0; i < queries.size(); i++) {
        if (ans[i].empty()) ans[i] = "not found";
    }
}

void Aho_Corasick_2D(vector<vector<char>> grid, vector<string> pattern, vector<string>& pos, long long& total_comparisons) {
    trie.push_back(TrieNode());
    for (int i = 0; i < pattern.size(); ++i) {
        insert(pattern[i], i);
    }

    build_failure_links();

    Aho_Corasick(grid, pattern, pos, total_comparisons);
}