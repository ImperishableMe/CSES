#include <bits/stdc++.h>
using namespace std;

int const N = 1'000'10;
int const INF = 1e9;
int const M = 1e9 + 7;
vector<int> g[N];
int dp[N];// step[N];
bool vis[N];
int n, m;
vector<int> order;

inline void addMod(int &a, int b){
    a += b;
    if (a >= M) a -= M;
}

void dfs(int u){
    vis[u] = 1;
    if (u == n) {
        dp[u] = 1;
        return;
    }
    if (g[u].empty()){
        dp[u] = 0;
        return;
    }
    else dp[u] = 0;

    for (auto v : g[u]){
        if (!vis[v]) dfs(v);
        addMod(dp[u], dp[v]);
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }    
    dfs(1);

    cout << dp[1] << "\n";

    return 0;
}

