#include <bits/stdc++.h>
using namespace std;

int const N = 1e5 + 10;
vector<int> g[N];
int in[N], out[N];
int n, m;
vector<int> order;

void dfs(int u){

	while (g[u].size()){
		auto v = g[u].back();
		g[u].pop_back();
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
		in[b]++, out[a]++;
		g[a].push_back(b);
	}


	for (int i = 2; i <= n - 1; i++){
		if (in[i] != out[i]) {
			cout << "IMPOSSIBLE\n"; return 0;
		}
	}

	bool OneOkay = (out[1] - in[1] == 1);
	bool nOkay = (in[n] - out[n] == 1);

	if (!OneOkay || !nOkay) {
		cout << "IMPOSSIBLE\n"; return 0;
	}

	dfs(1);

	if (order.size() != m + 1) {
		cout << "IMPOSSIBLE\n"; return 0;
	}

	reverse(order.begin(), order.end());
	for (auto x : order) cout << x << " ";
	cout << "\n";


	// cout << "finally" << endl;

	return 0;
}