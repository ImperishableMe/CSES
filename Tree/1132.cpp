#include <bits/stdc++.h>
using namespace std;

int const N = 2e5 + 10;
int const INF = INT_MAX;

vector<vector<int>> g;
int dist[2][N];

void dfs(int u, int p, int pos){

    for (auto v : g[u]){
        if (v == p) continue;
        dist[pos][v] = dist[pos][u] + 1;
        dfs(v, u, pos);
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

    dfs(1, -1, 0);

    int a = max_element(dist[0] + 1, dist[0] + n + 1) - dist[0];

    dist[1][a] = 0;

    dfs(a, -1, 1);

    int b = max_element(dist[1] + 1, dist[1] + n + 1) - dist[1];


    // cout << "dim " << a << " " << b << endl;

    dist[0][b] = 0;
    dfs(b, -1, 0);

    for (int i = 1; i <= n; i++){
        cout << max(dist[0][i], dist[1][i]) << " ";
    }
    cout << endl;
}