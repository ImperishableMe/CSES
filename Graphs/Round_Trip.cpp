#include <bits/stdc++.h>
using namespace std;

int const N = 1'000'10;
vector<int> g[N];
bool vis[N];
vector <int> stk;

void dfs(int u, int pr){
    stk.push_back(u);
    vis[u] = 1;
    for (auto v : g[u]){
        if (v == pr) continue;
        if (vis[v]) {
            vector <int> cycls;

            while (stk.size() and stk.back() != v){
                cycls.push_back(stk.back());
                stk.pop_back();
            }
            cycls.push_back(v);
            cycls.push_back(cycls.front());

            cout << cycls.size() << "\n";
            for (auto x : cycls) cout << x << " ";
            cout << "\n";

            exit(0);
        }
        dfs(v, u);
    }
    stk.pop_back();
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    for (int i = 1; i <= n; i++){
        if (!vis[i]) dfs(i, -1);
    }

    cout << "IMPOSSIBLE\n";
}

