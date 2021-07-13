#include <bits/stdc++.h>
using namespace std;

using ll = long long int;
using tp = tuple<int,int,ll>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int const N = 1e5 + 10;
int par[N], comp[N];

int Find(int u){
	return par[u] = (u == par[u])? u : Find(par[u]);
}

bool Union(int u, int v){
	int U = Find(u);
	int V = Find(v);
	if (U != V) {
		if (rng() % 2) swap(U, V);
		par[U] = V;
		comp[V] += comp[U];
		return true;
	}
	return false;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++) par[i] = i, comp[i] = 1;
	vector<tp> e;
	for (int i = 0; i < m; i++){
		int a, b, c;
		cin >> a >> b >> c;
		e.emplace_back(a,b,c);
	}
	sort(e.begin(), e.end(), [](tp a, tp b)->bool{
		return get<2>(a) < get<2>(b);
	});

	ll ans = 0;
	for (auto [u, v, w]: e){
		if (Union(u, v)){
			ans += w;
		}
	}
	if (comp[Find(1)] != n){
		cout << "IMPOSSIBLE\n";
	}
	else {
		cout << ans << "\n";
	}
}