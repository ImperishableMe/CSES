#include <bits/stdc++.h>
using namespace std;
int const N = 1'000'10;
using ll = long long int;
using PLL = pair<ll,ll>;
ll const INF = 1e18;

vector<PLL> g[N];
ll dist[N];

void dijkastra(int s) {
    dist[s] = 0;
    priority_queue<PLL, vector<PLL>, greater<PLL> > pq;
    pq.push({0, s});
    while (pq.size()){
        auto [d, u] = pq.top(); pq.pop();
        if (dist[u] < d) continue;

        for (auto [v, cost] : g[u]){
            if (dist[u] + cost < dist[v]){
                dist[v] = dist[u] + cost;
                pq.push({dist[v], v});
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m;
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
    }
    fill(dist, dist + n + 1, INF);
    dijkastra(1);


    for (int i = 1; i <= n; i++) cout << dist[i] << " ";
    cout << endl;
    
    return 0;
}