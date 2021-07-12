#include <bits/stdc++.h>
using namespace std;

int const N = 1'000'10;
int const INF = 1e9;
vector<int> g[N];
int dp[N], step[N];
bool vis[N];
int n, m;
vector<int> order;

void dfs(int u){
    vis[u] = 1;
    if (u == n) {
        dp[u] = 1;
        return;
    }
    if (g[u].empty()){
        dp[u] = -INF;
        return;
    }
    else dp[u] = 1;
    // cout << u << " " << dp[u] << endl;

    int mx = -INF;
    for (auto v : g[u]){
        if (!vis[v]) dfs(v);
        if (dp[v] > mx){
            mx = dp[v];
            step[u] = v;
        }
    }
    // cout << "again " << u << " " << mx << endl;

    if (mx == -INF) dp[u] = mx;
    else 
        dp[u] +=  mx;
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

    // for (int i = 1; i <= n; i++) cout << dp[i] << " ";
    // cout << endl;

    if (dp[1] == -INF) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << dp[1] << "\n";
    vector<int> path;
    // path.push_back(n);
    int cur = 1;
    while (cur != n){
        path.push_back(cur);
        cur = step[cur];
    }
    path.push_back(n);
    // reverse(path.begin(), path.end());
    for (auto x : path) cout << x << " ";
    cout << endl;
}

