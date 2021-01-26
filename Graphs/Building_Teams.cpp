#include <bits/stdc++.h>
using namespace std;
int const N = 1'000'10;

int col[N];
bool vis[N];
vector <int> g[N];

void dfs(int u, int _col) {
    col[u] = _col;
    vis[u] = 1;

    for (auto v : g[u]){
        if (vis[v] and col[v] == _col) {
            cout << "IMPOSSIBLE\n"; exit(0);
        }
        if (vis[v]) continue;
        dfs(v, _col ^ 1);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 1; i <= n; i++){
        if (vis[i]) continue;
        dfs(i, 0);
    }

    for (int i = 1; i <= n; i++) cout << col[i] + 1 << " ";
    cout << '\n';
    return 0;
}