#include <bits/stdc++.h>
using namespace std;

int const N = 2e5 + 10;

vector<vector<int>> g;
int dp[N][2];

void dfs(int u, int p){
    int sum = 0;
    for (int i = 0; i < g[u].size(); i++){
        int v = g[u][i];
        if (v == p) continue;
        dfs(v, u);
        sum += max(dp[v][0], dp[v][1]);
    }
    dp[u][0] = sum;

    for (auto v : g[u]){    
        if (v == p) continue;
        dp[u][1] = max(dp[u][1], 
            1 + sum - max(dp[v][0], dp[v][1]) + dp[v][0]
        );
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    g.assign(n+1, vector<int>());

    for (int i = 1; i <= n - 1; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    cout << max(dp[1][0], dp[1][1]) << '\n';
}