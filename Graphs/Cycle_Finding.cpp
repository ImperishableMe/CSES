#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using tp = tuple<int,int,ll>;


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<tp> e;

	for (int i = 0; i < m; i++) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		e.emplace_back(a,b,c);
	}

	ll inf = 1e16;

	int x = -1;
	vector<ll> dist(n+1, 0), par(n+1, -1);
	for (int i = 0; i < n; i++){
		x = -1;
		for (auto [u, v, w] : e){
			ll can = dist[u] + w;
			if (can < dist[v]){
				dist[v] = can;
				par[v] = u;
				x = v;
			}
		}
	}
	if (x == -1){
		cout << "NO\n";
	}
	else {
		for (int i = 0; i < n; i++) x = par[x];

		vector<int> cycle;
		int v = x;
		cycle.push_back(x);
		while (v != x || cycle.size() <= 1){
			v = par[v];
			cycle.push_back(v);
		}

		cout << "YES\n";
		reverse(cycle.begin(), cycle.end());
		for (auto x : cycle) cout << x << " ";
		cout << "\n";
	}

	return 0;
}