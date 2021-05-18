#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const N = 2e5 + 10;

vector<vector<int>> g;
int n, k, sub[N];
ll cnt[N], ans;
bool done[N];

int max_h = 0;

void calc_sub(int u, int p){
    sub[u] = 1;
    for (auto v : g[u]){
        if (v == p || done[v]) continue;
        calc_sub(v, u);
        sub[u] += sub[v];
    }
}


int centroid(int u, int p, int sz){
    for (auto v : g[u]){
        if (v != p && !done[v] && sub[v] > sz/2) 
            return centroid(v, u, sz);
    }
    return u;
}


void dfs(int u, int p, bool add, int d = 0){
    if (d > k) return;
    max_h = max(max_h, d); 

    if (add) cnt[d]++;
    else ans += cnt[k-d];

    for (auto v: g[u]){
        if (v != p && !done[v]){
            dfs(v, u, add, d+1);
        }
    }
}

void complete_this_centroid(int cen){
    cnt[0] = 1;

    for (auto v : g[cen]){
        if (done[v]) continue;
        dfs(v, cen, 0, 1);
        dfs(v, cen, 1, 1);
    }
}

void decompose(int u, int p){
    calc_sub(u, p);
    int cen = centroid(u, p, sub[u]);
    max_h = 0;

    complete_this_centroid(cen);
    done[cen] = 1;

    fill(cnt, cnt + max_h + 1, 0);

    for (auto v : g[cen]){
        if(!done[v])
            decompose(v, v);
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    g.assign(n+1, vector<int>());

    for (int i = 1; i <= n - 1; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }    

    decompose(1, 1);
    cout << ans << '\n';
    return 0;
}