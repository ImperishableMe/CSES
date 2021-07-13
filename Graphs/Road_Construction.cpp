#include <bits/stdc++.h>
using namespace std;

using ll = long long int;
using tp = tuple<int,int,ll>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int const N = 1e5 + 10;
int par[N], comp[N];

multiset<int> ms;

int Find(int u){
	return par[u] = (u == par[u])? u : Find(par[u]);
}

void Union(int u, int v, ll w){
	int U = Find(u);
	int V = Find(v);

	// cout << "current " << U << " " << V << endl;

	if (U != V) {
		if (rng() % 2) swap(U, V);
		int cu = comp[U];
		int cv = comp[V];

		assert(ms.find(cu) != ms.end());
		assert(ms.find(cv) != ms.end());

		ms.erase(ms.find(cu));
		ms.erase(ms.find(cv));

		par[U] = V;
		comp[V] += comp[U];
		ms.insert(comp[V]);
	}
	cout << ms.size() << " " << *ms.rbegin() << "\n";
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++) par[i] = i, comp[i] = 1, ms.insert(1);

	vector<tp> e;	
	for (int i = 0; i < m; i++){
		int a, b, c;
		cin >> a >> b ;//>> c;
		Union(a, b, 0);
	}

}