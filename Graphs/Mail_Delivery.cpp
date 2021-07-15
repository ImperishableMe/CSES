#include <bits/stdc++.h>
using namespace std;

int const N = 1e5 + 10;
set<int> g[N];
bool vis[N];
int adj_sz[N], cur_sz[N];
int n, m;
vector<int> order;

void dfs(int u){

	while (g[u].size()){
		auto v = *g[u].begin();
		g[u].erase(g[u].begin());
		g[v].erase(u);
		dfs(v);
	}
	order.push_back(u);
}

int main(){

	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	vector<int> deg(n+1, 0);

	for (int i = 1; i <= m; i++){
		int a, b;
		cin >> a >> b;
		deg[a]++, deg[b]++;
		g[a].insert(b);
		g[b].insert(a);
		adj_sz[a]++, adj_sz[b]++;
	}

	for (int i = 1; i <= n; i++) cur_sz[i] = adj_sz[i];

	for (int i = 1; i <= n; i++){
		if (deg[i] & 1) {
			cout << "IMPOSSIBLE\n"; return 0;
		}
	}

	dfs(1);

	for (int i = 1; i <= n; i++){
		if (!vis[i]) {
			cout << "IMPOSSIBLE\n"; return 0;
		}
	}

	for (auto x : order) cout << x << " ";
	cout << "\n";


	// cout << "finally" << endl;

	return 0;
}