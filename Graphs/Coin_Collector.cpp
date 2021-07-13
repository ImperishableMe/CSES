#include <bits/stdc++.h>
using namespace std;

using ll = long long int;

int const N = 1e5 + 10;
vector<vector<int>> g, rg;
bool vis[N];
vector<int> root_nodes; // the root nodes representing condensation graph
vector<int> which_root; // under which root_node a node 'x' is
vector<int> adj_scc[N]; // edges of the condensation graph
vector<int> order;		// for t_out order
vector<int> comp;    	// will hold the current SCC

vector<ll> coin_in_comp, dp;

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

	vector<ll> k(n+1);

	g.resize(n+1);
	rg.resize(n+1);
	which_root.resize(n+2);
	coin_in_comp.resize(n+2);
	dp.assign(n+2, 0);


	for (int i = 1; i <= n; i++) cin >> k[i];

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
				which_root[x] = i;
				coin_in_comp[i] += k[x];
			}
		}
	}
	for (int i = 1; i <= n; i++){
		for (auto v : g[i]){
			if (which_root[i] == which_root[v]) continue;
			adj_scc[which_root[i]].push_back(which_root[v]);
		}
	}

	fill(dp.begin(), dp.end(), 0);

	for (int i = (int)root_nodes.size()-1; i >= 0; i--){
		int node = root_nodes[i];
		int comp_root = which_root[node];
		dp[node] = coin_in_comp[comp_root];
		ll mx = 0;
		for (auto x : adj_scc[node]){
			mx = max(mx, dp[x]);
		}
		dp[node] += mx;
	}

	cout << *max_element(dp.begin(), dp.end()) << "\n";
	
	return 0;
}