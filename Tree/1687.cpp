#include <bits/stdc++.h>
using namespace std;

int const N = 2e5 + 10;
int const LOG = 19;
vector<vector<int>> g;
int dp[LOG][N];

void dfs(int u, int p = -1){
    dp[0][u] = p;
    for (auto v : g[u]){
        dfs(v, u);
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;
    g.assign(n+1, vector<int>());

    for (int i = 2; i <= n; i++){
        int boss;
        cin >> boss;
        g[boss].push_back(i);
    }
    memset(dp, -1, sizeof dp);
    dfs(1);

    for (int i = 1; i < LOG; i++){
        for (int j = 1; j <= n; j++){
            dp[i][j] = dp[i-1][j] == -1? -1: dp[i-1][dp[i-1][j]];
        }
    }

    while (q--){
        int x, k;
        cin >> x >> k;
        int ans = x;
        for (int i = LOG - 1; i >= 0; i--){
            if ((1<<i) & k){
                ans = dp[i][ans];
                if (ans == -1) break;
            }
        }

        cout << ans << "\n";
    }
}