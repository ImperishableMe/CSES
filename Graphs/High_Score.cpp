#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using PLL = pair<ll,ll>;
int const N = 35'00;
vector<PLL> g[N];
bool vis[N];

void dfs(int u){
	vis[u] = 1;
	for (auto [v, _]: g[u]){
		if (!vis[v]) dfs(v);
	}
}


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> st(m), en(m), c(m);
	for (int i = 0; i < m; i++) {
		cin >> st[i] >> en[i] >> c[i];
		g[en[i]].push_back({st[i], c[i]});
	}
	vector<ll> dist(n+1, -1e16), finDist(n+1, -1e16);
	dist[1] = 0;
	for (int i = 0; i < n - 1; i++){
		for (int j = 0; j < m; j++){
			ll can = dist[st[j]] + c[j];
			if (dist[en[j]] < can) dist[en[j]] = can;
		}
	}
	ll cur = dist[n];
	set <int> harami;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			ll can = dist[st[j]] + c[j];
			if (dist[en[j]] < can) {
				dist[en[j]] = can;
				harami.insert(en[j]);
			}
		}
	}

	dfs(n);

	for (auto x : harami){
		if (dist[x] > -1e15 && vis[x]) {
			cout << "-1\n"; return 0;
		}
	}
	cout << cur << "\n";

	return 0;
}