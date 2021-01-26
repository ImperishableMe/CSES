#include <bits/stdc++.h>
using namespace std;

int const N = 1'000'10;
int par[N], sz[N];

int find_par(int u){
    return par[u] = (u == par[u])? u : find_par(par[u]);
}

void dsu_merge(int u, int v) {
    int U = find_par(u);
    int V = find_par(v);

    if (U != V) {
        if (sz[U] > sz[V]) swap(U, V);
        par[U] = V;
        sz[U] += sz[V];
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) par[i] = i, sz[i] = 1;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        dsu_merge(a, b);
    } 
    vector < int > comps_parents;

    for (int i = 1; i <= n; i++) {
        if (find_par(i) == i) comps_parents.push_back(i);
    }

    cout << (int)comps_parents.size() - 1 << "\n";

    for (int i = 0; i + 1 < comps_parents.size(); i++) {
        cout << comps_parents[i] << " " << comps_parents[i+1] << '\n';
    }
    return 0;
}