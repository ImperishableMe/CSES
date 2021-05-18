#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const N = 2e5 + 10;
vector<vector<int>> g;
int tin[N], tout[N], tmap[N], c[N], sub[N], big[N];
int timer;
int ans[N];
int cnt[N];

// set <int> *st[N];


void dfs(int u, int p, ll s = 0){
    tin[u] = ++timer;
    tmap[timer] = u;
    sub[u] = 1;
    big[u] = -1;
    int bigSize = 0;

    for (auto v : g[u]){
        if (v == p) continue;
        dfs(v, u);
        sub[u] += sub[v];
        if (sub[v] > bigSize) {
            big[u] = v;
            bigSize = sub[v];
        }
    }
    tout[u] = timer;
}

int curAns = 0;

void add(int u){
    u = c[u];
    cnt[u]++;
    if (cnt[u] == 1) curAns++;
}

void remove(int u){
    u = c[u];
    cnt[u]--;
    if (cnt[u] == 0) curAns--;
}

void dsu(int u, int p, bool keep = 0){

    for (auto v : g[u]){
        if (v == p || v == big[u])continue;
        dsu(v, u, 0);
    }

    if (big[u] != -1) dsu(big[u], u, 1);

    add(u);


    for (int v: g[u]){
        if (v == p || v == big[u]) continue;

        for (int i = tin[v]; i <= tout[v]; i++){
            add(tmap[i]);
        }
    }
    
    ans[u] = curAns;

    if (!keep){

        for (int i = tin[u]; i <= tout[u]; i++){
            remove(tmap[i]);
        }
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n;
    g.assign(n+1, vector<int>());


    for (int i = 1; i <= n; i++) cin >> c[i];
    map<int, int> cmap;

    for (int i = 1; i <= n; i++){
        if (!cmap.count(c[i])){
            cmap[c[i]] = cmap.size();
        }
    }

    for (int i = 1; i <= n; i++) c[i] = cmap[c[i]];

    // for (int i = 1; i <= n; i++){
    //     cout << i << "  col " << c[i] << endl;
    // }

    for (int i = 2; i <= n; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 1); 

    dsu(1, 1, 0);

    for (int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
    cout << endl;

}