#include <bits/stdc++.h>
using namespace std;

int const N = 1'000'10;
int const INF = 1e9;
vector <int> g[N];
int dist[N], par[N];

void bfs(int s){
    dist[s] = 0, par[s] = s;
    
    queue<int> q;
    q.push(s);

    while(q.size()){
        int u = q.front(); q.pop();
        for (auto v : g[u]){
            if (dist[v] == INF){
                dist[v] = dist[u] + 1;
                par[v] = u;
                q.push(v);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m;
    cin >> n >> m;

    memset(par, -1, sizeof par);
    fill(dist, dist + n + 1, INF);

    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    
    bfs(1);

    if (dist[n] == INF) {
        cout << "IMPOSSIBLE\n";
    }
    else {
        cout << dist[n] + 1 << "\n";
        vector <int> path;
        int target = n;

        while (par[target] != target) {
            path.push_back(target);
            target = par[target];
        }
        assert(target == 1);
        path.push_back(target);

        reverse(path.begin(), path.end());

        for (int i = 0; i < path.size(); i++){
            cout << path[i] ;
            if (i + 1 != path.size()) cout << " ";
            else cout << "\n";
        }
    }

    return 0;
}