#include <bits/stdc++.h>
using namespace std;

using ll = long long int;
using PLL = pair<ll,ll>;

int const N = 1'000'10;
ll const INF = 1e16;
int const M = 1e9 + 7;
vector<PLL> g[N];
ll minVal[N], ways[N], minC[N], maxC[N]; 
bool vis[N];
int n, m;

inline void addMod(ll &a, ll b){
    a += b;
    if (a >= M) a -= M;
}

void dijkastra(int src){
    fill(minVal, minVal+n+1, INF);

    priority_queue<PLL, vector<PLL>, greater<PLL>> pq;

    pq.push({0, src});
    minVal[src] = 0;
    maxC[src] = 0;
    minC[src] = 0;
    ways[src] = 1;

    while (!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();

        if (d > minVal[u]) continue;

        for (auto [v, w]: g[u]){
            ll can = minVal[u] + w;
            if (can < minVal[v]){
                minVal[v] = can;
                ways[v] =  ways[u];
                minC[v] = minC[u] + 1;
                maxC[v] = maxC[u] + 1;
                pq.push({can, v});
            }
            else if (can == minVal[v]){
                minC[v] = min(minC[v], minC[u] + 1);
                maxC[v] = max(maxC[v], maxC[u] + 1);
                addMod(ways[v], ways[u]);
            }
        }
    }
    
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }    
    dijkastra(1);

    cout << minVal[n] << " " << ways[n] << " " << minC[n] << " " << maxC[n] << endl;

    return 0;
}

