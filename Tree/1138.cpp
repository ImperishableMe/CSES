#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const N = 2e5 + 10;
vector<vector<int>> g;
ll sub[N], sum[N], val[N], bit[N];
int tin[N], tmap[N];
int timer;

void dfs(int u, int p, ll s = 0){
    tin[u] = ++timer;
    tmap[timer] = u;
    sub[u] = 1;
    sum[u] = val[u] + s;

    for (auto v : g[u]){
        if (v == p) continue;
        dfs(v, u, sum[u]);
        sub[u] += sub[v];
    }
}

void update(int pos, ll val){
    for (; pos < N; pos += (pos & (-pos))){
        bit[pos] += val;
    }
} 

ll Q(int b){
    ll ret = 0;
    for (; b > 0; b -= (b & (-b))){
        ret += bit[b];
    }
    return ret; 
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q;
    cin >> n >> q;
    g.assign(n+1, vector<int>());


    for (int i = 1; i <= n; i++) cin >> val[i];

    for (int i = 2; i <= n; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(1, 1); 


    for (int t = 1; t <= timer; t++){
        update(t, sum[tmap[t]] - sum[tmap[t-1]]);
    }


    // for (int i = 1; i <= n; i++){
    //     cout <<"val "<< i << " " << Q(tin[i]) << endl;
    // }

    while (q--){
        int t;
        cin >> t;
        if (t == 1){
            ll s, x;
            cin >> s >> x;
            update(tin[s], x - val[s]); 
            update(tin[s] + sub[s], val[s] - x);
            val[s] = x;
        }
        else {
            int s;
            cin >> s;
            cout << Q(tin[s]) << "\n";
        }
    }
}