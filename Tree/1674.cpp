#include <bits/stdc++.h>
using namespace std;

int const N = 2e5 + 10;

int sub[N];
vector<vector<int>> g;

void dfs(int u){
    sub[u] = 1;
    for (auto v : g[u]) {
        dfs(v);
        sub[u] += sub[v];
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    g.assign(n+1, vector<int>());

    for (int i = 2; i <= n; i++){
        int boss;
        cin >> boss;
        g[boss].push_back(i);
    }

    dfs(1);

    for (int i = 1; i <= n; i++){
        cout << sub[i] - 1 << " ";
    }
    cout << endl;
}