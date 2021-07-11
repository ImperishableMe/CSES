#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using PLL = pair<ll,ll>;
int const N = 1e5 + 10;
vector<vector<PLL>> g, rg;
bool vis[N];
ll d_1[N], d_n[N];

/// dijkastra using priority_queue
void dijkastra(int src, vector<vector<PLL>> &aj, ll dist[]){
	priority_queue<PLL, vector<PLL>, greater<PLL>> pq;
	dist[src] = 0;
	pq.push({0, src});

	while (!pq.empty()){
		auto [d, u] = pq.top();
		pq.pop();
		if (dist[u] < d) continue;
		for (auto [v, w]: aj[u]){
			ll can = dist[u] + w;
			if (can < dist[v]) {
				dist[v] = can;
				pq.push({dist[v], v});
			}
		}
	}
}


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;
	g.assign(n+1, vector<PLL>());
	rg.assign(n+1, vector<PLL>());

	for (int i = 0; i < m; i++){
		int a, b, c;
		cin >> a >> b >> c;
		g[a].push_back({b, c});
		rg[b].push_back({a, c});
	}

	ll inf = 1e17;
	fill(d_1, d_1 + n+1, inf);
	fill(d_n, d_n + n+1, inf);

	dijkastra(1, g, d_1);

	fill(vis, vis+n+1, 0);

	dijkastra(n, rg, d_n);

	ll mn_cost = d_1[n];

	// for (int i = 1; i <= n; i++) cout << d_1[i] << " ";
	// cout << endl;

	for (int i = 1; i <= n; i++){
		for (auto [v, c] : g[i]){
			ll can = d_1[i] + d_n[v] + (c/2);
			mn_cost = min(mn_cost, can);
		}
	}
	cout << mn_cost << "\n";

	return 0;
}