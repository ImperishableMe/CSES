#include <bits/stdc++.h>
using namespace std;

int const N = 2e5 + 10;
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
	int sz = 2*(m+2);
	g.resize(sz);
	rg.resize(sz);
	which_root.resize(sz);

	for (int i = 0; i < n; i++){
		char c1, c2;
		int a, b;
		cin >> c1 >> a >> c2 >> b;
		// cout << c1 << " " << a << " " << c2 << " " << b << endl;

		g[2*a + (c1 == '+')].push_back(2*b + (c2 == '-'));
		g[2*b + (c2 == '+')].push_back(2*a + (c1 == '-'));
	}


	for (int i = 1; i <= 2*m+1; i++){
		// cout << "node " << i << endl;
		for (auto v : g[i]){
			// cout << v << " ";
			rg[v].push_back(i);
		}
		// cout << endl;
	}

	fill(vis, vis + sz + 1, false);
	for (int i = 1; i <= 2*m+1; i++){
		if (!vis[i]){
			dfs1(i);
		}
	}

	reverse(order.begin(), order.end());

	fill(vis, vis + sz + 1, false);
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

	// cout << root_nodes.size() << "\n";

	// for (int i = 1; i <= n; i++) cout << which_root[i] << " ";
	// cout << "\n";
	vector<char> ans;
	for (int i = 1; i <= m; i++){
		if (which_root[2*i] == which_root[2*i+1]){
			cout << "IMPOSSIBLE\n";
			exit(0);
		}
		char ch = ((which_root[2*i] > which_root[2*i+1])?'+':'-');
		ans.push_back(ch);
	}
	for (auto ch : ans) cout << ch;
	cout << "\n";

	return 0;
}