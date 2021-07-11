#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using PLL = pair<ll,ll>;
int const K = 15;
int const N = 1e5 + 10;
ll const INF = 1e16;
vector<vector<ll>>d;
vector<PLL> g[N];
int n, m, k;

void dijkastra(int src){
	d.resize(n+1);
	
	for (int i = 1; i <= n; i++) {
		d[i] = vector(k, INF);
	}
	// cout << "hello" << endl;
	d[src][0] = 0;
	priority_queue<PLL, vector<PLL>, greater<PLL>> pq;
	pq.push({0, src});
	while (!pq.empty()){
		auto [cost, u] = pq.top();
		// cout << cost << " " << u << endl;
		pq.pop();
		
		if (d[u].back() < cost) continue;

		for (auto [v, w] : g[u]){
			int cur = -1;
			ll can = cost + w;
			for (int i = 0; i < k; i++){
				if (d[v][i] >= can) {
					cur = i; break;
				}
			}
			if (cur == -1) continue;		
			else {
				rotate(d[v].begin()+cur, d[v].end()-1, d[v].end());
				d[v][cur] = can; 
				pq.push({can, v});
			}
		}
	}
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++){
		int a, b, c;
		cin >> a >> b >> c;
		g[a].emplace_back(b, c);
	}


	dijkastra(1);

	for (int i = 0; i < k; i++) cout << d[n][i] << " \n"[i+1==k];
	return 0;
}