#include <bits/stdc++.h>
using namespace std;

int const N = 1e5 + 10;
vector<vector<int>> g, rg;
bool vis[N];

void dfs(int u, vector<vector<int>> &aj){
	vis[u] = 1;
	for (auto v : aj[u]){
		if (!vis[v]) dfs(v, aj);
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;

	g.resize(n+1);
	rg.resize(n+1);

	for (int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		rg[b].push_back(a);
	}
	fill(vis, vis + n + 1, false);
	dfs(1, g);
	for (int i = 1; i <= n; i++){
		if (!vis[i]){
			cout << "NO\n";
			cout << "1 " << i << "\n"; exit(0);
		}
	}

	fill(vis, vis + n + 1, false);
	dfs(1, rg);
	for (int i = 1; i <= n; i++){
		if (!vis[i]){
			cout << "NO\n";
			cout << i << " 1\n"; exit(0);
		}
	}

	cout << "YES\n";

	return 0;
}