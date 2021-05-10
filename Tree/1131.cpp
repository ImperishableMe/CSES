#include <bits/stdc++.h>
using namespace std;

int const N = 2e5 + 10;
int const INF = INT_MAX;

vector<vector<int>> g;
vector<int> dist;

void dfs(int u, int p){

    for (auto v : g[u]){
        if (v == p) continue;
        dist[v] = dist[u] + 1;
        dfs(v, u);
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    cin >> n;
    g.assign(n+1, vector<int>());
    dist.assign(n+1, 0);

    for (int i = 1; i <= n - 1; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1, -1);

    int dim_node = max_element(dist.begin()+1, dist.end()) - dist.begin();

    dist[dim_node] = 0;
    dfs(dim_node, -1);

    cout << *max_element(dist.begin()+1, dist.end()) << endl;

}