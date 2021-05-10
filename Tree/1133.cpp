#include <bits/stdc++.h>
using namespace std;

using ll = long long int;
int const N = 2e5 + 10;
int const INF = INT_MAX;

vector<vector<int>> g;
ll sub[N], dp[N], ans[N];
int n;

void dfs(int u, int p){
    sub[u] = 1;
    for (auto v : g[u]){
        if (v == p) continue;
        dfs(v, u);
        sub[u] += sub[v];
        dp[u] += dp[v] + sub[v];
    }
}

void dfs1(int u, int p){
    ans[u] = dp[u];

    if (p != -1){
        ans[u] += (ans[p] - dp[u] + n - 2 * sub[u]);
    }
    for (auto v : g[u]){
        if (v == p) continue;
        dfs1(v, u);
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    g.assign(n+1, vector<int>());

    for (int i = 1; i <= n - 1; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);
    dfs1(1, -1);

    for (int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
    cout << endl;

}