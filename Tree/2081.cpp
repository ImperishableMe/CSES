#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const N = 2e5 + 10;

vector<vector<int>> g;
ll bit[N];
int n, k1, k2, sub[N];
ll ans;
bool done[N];
int max_h = 0;

void update(int pos, ll val){
    pos++;
    for (; pos < N; pos += (pos & (-pos))) bit[pos] += val;
}

ll Q(int l, int r){
    ll ret = 0;
    for (r++ ; r ; r -= (r & (-r))) ret += bit[r];
    for (; l ; l -= (l & (-l))) ret -= bit[l];
    return ret;
}

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
    if (d > k2) return;
    max_h = max(max_h, d); 

    if (add) {
        update(d, 1);
    }
    else{
        ans += Q(max(0, k1 - d), k2 - d);
    } 

    for (auto v: g[u]){
        if (v != p && !done[v]){
            dfs(v, u, add, d+1);
        }
    }
}

void complete_this_centroid(int cen){

    max_h = 0;
    for (auto v : g[cen]){
        if (done[v]) continue;
        dfs(v, cen, 0, 1);
        dfs(v, cen, 1, 1);
    }
    done[cen] = 1;

    for (int i = 1; i <= max_h; i++) update(i, -Q(i,i));

}

void decompose(int u, int p){
    calc_sub(u, p);
    int cen = centroid(u, p, sub[u]);

    complete_this_centroid(cen);

    for (auto v : g[cen]){
        if(!done[v])
            decompose(v, v);
    }
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k1 >> k2;
    g.assign(n+1, vector<int>());

    for (int i = 1; i <= n - 1; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }    

    update(0, 1);
    decompose(1, 1);
    cout << ans << '\n';
    return 0;
}