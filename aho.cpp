#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

struct Result {
    int r1, c1, r2, c2;
};



struct TrieNode {
    TrieNode* children[26];
    TrieNode* fail;
    vector<string> matched_words;

    TrieNode() {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
        fail = nullptr;
    }
};

void insert(const string& word, TrieNode* root) {
    TrieNode* curr = root;
    for (char c : word) {
        int index = c - 'a';
        if (curr->children[index] == nullptr) {
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index];
    }
    curr->matched_words.push_back(word);
}

void build_failure_links(TrieNode* root) {
    queue<TrieNode*> q;
    root->fail = root;

    for (int i = 0; i < 26; i++) {
        if (root->children[i] != nullptr) {
            root->children[i]->fail = root;
            q.push(root->children[i]);
        }
    }

    // BFS IMPLEMENT
    while (!q.empty()) {
        TrieNode* u = q.front();
        q.pop();

        for (int i = 0; i < 26; i++) {
            if (u->children[i] != nullptr) {
                TrieNode* v = u->children[i];
                TrieNode* f = u->fail;

                while (f != root && f->children[i] == nullptr) {
                    f = f->fail;
                }

                if (f->children[i] != nullptr) {
                    v->fail = f->children[i];
                } else {
                    v->fail = root;
                }

                for (const string& w : v->fail->matched_words) {
                    v->matched_words.push_back(w);
                }

                q.push(v);
            }
        }
    }
}



void free_memory(TrieNode* node) {
    if (node == nullptr) return;
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            free_memory(node->children[i]);
        }
    }
    delete node;
}

void Aho_Corasick_SEARCH(const string& text, const vector<pair<int, int>>& coords, TrieNode* root, map<string, vector<Result>>& results,int& comparison) {
    TrieNode* curr = root;
    for (int i = 0; i < text.length(); i++) {
        int index = text[i] - 'a';
        comparison++;
        while (curr != root && curr->children[index] == nullptr) {
            curr = curr->fail;
            comparison++;
        }

        if (curr->children[index] != nullptr) {
            curr = curr->children[index];
        }

        for (const string& word : curr->matched_words) {
            int len = word.length();
            int start_idx = i - len + 1;
            int end_idx = i;

            results[word].push_back({
                coords[start_idx].first, coords[start_idx].second,
                coords[end_idx].first, coords[end_idx].second
            });
        }
    }
}

void Aho_Corasick(const vector<vector<char>>& grid, TrieNode* root, const vector<string>& queries) {
    int rows = grid.size();
    if (rows == 0) return;
    int cols = grid[0].size();
    int comparison = 0;
    map<string, vector<Result>> results;

    for (int r = 0; r < rows; r++) {
        string text_fwd = "", text_rev = "";
        vector<pair<int, int>> coords_fwd, coords_rev;

        for (int c = 0; c < cols; c++) {
            text_fwd += grid[r][c];
            coords_fwd.push_back({r, c});
            text_rev += grid[r][cols - 1 - c];
            coords_rev.push_back({r, cols - 1 - c});
        }
        Aho_Corasick_SEARCH(text_fwd, coords_fwd, root, results,comparison);
        Aho_Corasick_SEARCH(text_rev, coords_rev, root, results,comparison);
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
        Aho_Corasick_SEARCH(text_fwd, coords_fwd, root, results,comparison);
        Aho_Corasick_SEARCH(text_rev, coords_rev, root, results,comparison);
    }

    for (const string& w : queries) {
        cout << w << ": ";
        if (results[w].empty()) {
            cout << "not found\n";
        } else {
            for (size_t i = 0; i < results[w].size(); i++) {
                cout << "(" << results[w][i].r1 << ", " << results[w][i].c1 << ") -> "
                     << "(" << results[w][i].r2 << ", " << results[w][i].c2 << ")";
                if (i < results[w].size() - 1) cout << "; ";
            }
            cout << ";\n";
        }
    }
    cout << "Comparisons: " << comparison << '\n';

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

    TrieNode* root = new TrieNode();

    vector<string> queries(q);
    for(int i = 0; i < q; i++) {
        cin >> queries[i];
        insert(queries[i], root);
    }

    build_failure_links(root);

    for (auto w : queries) {
        Aho_Corasick(grid, root,queries);
    }

    free_memory(root);
    return 0;
}