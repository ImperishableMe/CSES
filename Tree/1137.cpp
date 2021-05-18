#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int const N = 2e5 + 10;
vector<vector<int>> g;
ll tin[N], sub[N], val[N], bit[N];
int timer;

void dfs(int u, int p){
    tin[u] = ++timer;
    sub[u] = 1;

    for (auto v : g[u]){
        if (v == p) continue;
        dfs(v, u);
        sub[u] += sub[v];
    }
}

void update(int pos, ll val){
    for (; pos < N; pos += (pos & (-pos))){
        bit[pos] += val;
    }
} 

ll Q(int a, int b){
    ll ret = 0;
    for (; b > 0; b -= (b & (-b))){
        ret += bit[b];
    }
    a--;

    for (; a > 0; a -= (a & (-a))){
        ret -= bit[a];
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

    for (int i = 1; i <= n; i++){
        update(tin[i], val[i]);
    }

    while (q--){
        int t;
        cin >> t;
        if (t == 1){
            int s, x;
            cin >> s >> x;
            update(tin[s], x - val[s]);
            val[s] = x;
        }
        else {
            int s;
            cin >> s;
            cout << Q(tin[s], tin[s] + sub[s] - 1) << "\n";
        }
    }
}