#include <bits/stdc++.h>
using namespace std;

int const N = 1e5 + 10;
vector<vector<int>> g, rg;
bool vis[N];
vector<int> root_nodes; // the root nodes representing condensation graph
vector<int> which_root; // under which root_node a node 'x' is
vector<int> order, comp;

void dfs1(int u){
	vis[u] = 1;
	for (auto v : g[u]){
		if (!vis[v]) dfs1(v);
	}
	order.push_back(u);
}

void dfs2(int u){
	vis[u] = 1;
	comp.push_back(u);
	for (auto v : rg[u]){
		if (!vis[v]) dfs2(v);
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;

	g.resize(n+1);
	rg.resize(n+1);
	which_root.resize(n+1);

	for (int i = 0; i < m; i++){
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		rg[b].push_back(a);
	}
	fill(vis, vis + n + 1, false);
	for (int i = 1; i <= n; i++){
		if (!vis[i]){
			dfs1(i);
		}
	}

	reverse(order.begin(), order.end());

	fill(vis, vis + n + 1, false);
	for (auto i : order){
		if (!vis[i]){
			comp.clear();
			dfs2(i);
			// got the component in comp now
			root_nodes.push_back(i);
			for (auto x : comp){
				which_root[x] = root_nodes.size();
			}
		}
	}

	cout << root_nodes.size() << "\n";

	for (int i = 1; i <= n; i++) cout << which_root[i] << " ";
	cout << "\n";


	return 0;
}