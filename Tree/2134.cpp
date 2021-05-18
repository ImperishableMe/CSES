#include <bits/stdc++.h>
using namespace std;

#define L(x) (x)<<1
#define R(x) (x)<<1|1

using ll = long long int;
int const LOG = 19;
ll const IDENTITY = 0;

int const N = 2e5 + 10;
ll t[4*N];
ll a[N];
int dp[LOG][N], tin[N], tout[N];
int timer;
vector<vector<int>> g;
int heavy[N], sz[N], par[N], dep[N], head[N], pos[N], revPos[N];

ll merge(ll l, ll r){
    return max(l, r);
}

void build(int p, int l, int r){
    if (l == r) {
        t[p] = a[revPos[l]];
        return;
    }
    int mid = (l+r)/2;
    build(L(p), l, mid);
    build(R(p), mid+1, r);

    t[p] = merge(t[L(p)], t[R(p)]);
}

void update(int p, int l, int r, int ul, int ur, ll val){
    if (l > ur || r < ul) return;
    if (ul <= l && r <= ur) {
        t[p] = val;
        return;
    }
    int mid = (l+r)/2;
    update(L(p), l, mid, ul, ur, val);
    update(R(p), mid+1, r, ul, ur, val);

    t[p] = merge(t[L(p)], t[R(p)]);
}

ll Q(int p, int l, int r, int ql, int qr){
    if (l > qr || r < ql) return IDENTITY;
    if (ql <= l && r <= qr) return t[p];

    int mid = (l+r)/2;

    return merge(
        Q(L(p), l, mid, ql, qr),
        Q(R(p), mid+1, r, ql, qr)
    );
}


void dfs(int u, int p, int d = 0){
    int bigChild = -1, bigSize = 0;
    par[u] = dp[0][u] = p;
    dep[u] = d;            
    tin[u] = ++timer;
    sz[u] = 1;

    for (auto v : g[u]){
        if (v == p) continue;
        dfs(v, u, d + 1);
        sz[u] += sz[v];
        if (bigSize < sz[v]){
            bigSize = sz[v];
            bigChild = v;
        }
    }
    tout[u] = timer;
    heavy[u] = bigChild;
}

int cur_pos = 0;

void decompose(int u, int h){

    head[u] = h, pos[u] = ++cur_pos;
    revPos[cur_pos] = u;

    if (heavy[u] != -1) decompose(heavy[u], h);

    for (auto v : g[u]){
        if (v != par[u] && v != heavy[u]){
            decompose(v, v);
        }
    }
}
bool is_ancestor(int u, int v){
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v){
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;

    for (int i = LOG-1; i >= 0; i--){
        if (!is_ancestor(dp[i][u], v)) {
            u = dp[i][u];
        }
    }
    return dp[0][u];
}

int query(int chi, int up){
    ll res = 0;
    int cnt = 0;

    while (chi != up){

        if (head[chi] == chi){
            res = max(res, a[chi]);
            chi = par[chi];
        }
        else if(dep[head[chi]] > dep[up]){
            res = max(res, Q(1, 1, cur_pos, pos[head[chi]], pos[chi]));
            chi = par[head[chi]];
        }
        else {
            res = max(res, Q(1, 1, cur_pos, pos[up] + 1, pos[chi]));
            break;
        }
    }
    // cerr << "done " << endl;
    return res;
}


int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];

    g.assign(n+1, vector<int>());
    
    for (int i = 1; i <= n - 1; i++){
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    memset(heavy, -1, sizeof heavy);

    dfs(1, 1);
    decompose(1, 1);

    for (int i = 1; i < LOG; i++){
        for (int j = 1; j <= n; j++){
            dp[i][j] = dp[i-1][dp[i-1][j]];
        }
    }

    build(1, 1, cur_pos);

    while (q--){
        int t;
        cin >> t;
        if (t == 1){
            int s, x;
            cin >> s >> x;
            update(1, 1, cur_pos, pos[s], pos[s], x);
            a[s] = x;
        }
        else {
            int u, v;
            cin >> u >> v;
            int l = lca(u, v);
            cout << max(a[l], 1LL*max(query(u, l), query(v, l))) << " ";
            // cout << query(a, b) << " ";
        }
    }
    cout << "\n";
    // cerr << "TIME taken " << 1.0 * (clock() - t)/ CLOCKS_PER_SEC << "\n";
    
    return 0;
}