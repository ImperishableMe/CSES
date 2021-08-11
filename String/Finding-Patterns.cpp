#include <bits/stdc++.h>
using namespace std;
#define inf 1e8

int const ALPHA = 26;

struct Node {
    int to[ALPHA];
    bool leaf;
    int link;
    int ext;
    int lvl;
    vector<int> end_inds;
    Node() {
        leaf = link = ext = lvl = 0;
        for (int i = 0; i < ALPHA; i++)
            to[i] = 0;
    }
};

vector<Node> t;

void add(string &s, int ind) {
    int v = 0;
    for (auto ch : s) {
        if (!t[v].to[ch - 'a']) {
            t[v].to[ch - 'a'] = t.size();
            t.push_back(Node());
        }
        v = t[v].to[ch - 'a'];
    }
    t[v].leaf = 1;
    t[v].end_inds.push_back(ind);
}

void build_aho() {
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int p = q.front();
        q.pop();

        for (int ch = 0; ch < ALPHA; ch++) {
            int v = t[p].to[ch];

            if (v) {
                t[v].link = (p == 0) ? 0 : t[t[p].link].to[ch];

                if (t[t[v].link].leaf) {
                    t[v].ext = t[v].link;
                }
                else {
                    t[v].ext = t[t[v].link].ext;
                }
                t[v].lvl = t[p].lvl + 1;
                q.push(v);
            }
            else {
                t[p].to[ch] = t[t[p].link].to[ch];
            }
        }
    }
}

void run_on_automata(string &s, int k){
    vector<bool> pat_matched(k, 0);
    vector<bool> visited(t.size(), 0);

    queue<int> q;
    int v = 0;
    for (auto ch : s){
        v = t[v].to[ch - 'a'];
        q.push(v);
    }

    while(!q.empty()){
        int u = q.front(); q.pop();
        if (visited[u]) continue;
        visited[u] = 1;
        for (auto ind : t[u].end_inds) pat_matched[ind] = 1;
        if (!visited[t[u].ext]) q.push(t[u].ext);
    } 

    for (int i = 0; i < k; i++){
        cout << (pat_matched[i]?"YES":"NO") << "\n";
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tc = 1;

    for (int cs = 1; cs <= tc; cs++) {
        t.clear();
        t.push_back(Node());

        int k, n;
        string s;
        cin >> s;
        n = s.size();

        cin >> k;
        vector<string> pat(k);
        for (int i = 0; i < k; i++) {
            cin >> pat[i];
            add(pat[i], i);
        }
        build_aho();

        run_on_automata(s, k);
    }

    return 0;
}
