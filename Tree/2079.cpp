#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const N = 2e5 + 10;
vector<vector<int>> g;
int sub[N], mx[N];
int n;

void dfs(int u, int p, ll s = 0){
    sub[u] = 1;

    for (auto v : g[u]){
        if (v == p) continue;
        dfs(v, u);
        sub[u] += sub[v];
        mx[u] = max(mx[u], sub[v]);
    }
    mx[u] = max(mx[u], n - sub[u]);
}


int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    g.assign(n+1, vector<int>());


    for (int i = 2; i <= n; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, 1); 

    for (int i = 1; i <= n; i++){
        if (mx[i] <= n/2) {
            cout << i << endl;
            exit(0);
        }
    }
    assert(false);
    return 0;
}