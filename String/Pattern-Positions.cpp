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

vector<int> run_on_automata(string &s, int sz){

    vector<int> pat_matched(sz, INT_MAX);
    int v = 0;
    for (int i = 0; i < s.size(); i++){
        char ch = s[i];
        v = t[v].to[ch - 'a'];
        int tmp = v;
        while (tmp){
            for (auto ind : t[tmp].end_inds){
                pat_matched[ind] = min(pat_matched[ind], i);
            }
            tmp = t[tmp].ext;
        }
    }
    return pat_matched;
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
        map<string,int> pat;
        vector<string> p(k);
        for (int i = 0; i < k; i++) {
            string s;
            cin >> s;
            p[i] = s;
            if (!pat.count(s)){
                pat[s] = pat.size();
                add(s, pat[s]);
            }
        }
        build_aho();
        vector<int> mat = run_on_automata(s, pat.size());   

        for (auto &s : p) {
            int ending = mat[pat[s]];
            if (ending > 1e8) ending = -1;
            else ending -= (int)s.size() - 2;
            cout << ending << "\n";
        }
    }

    return 0;
}
