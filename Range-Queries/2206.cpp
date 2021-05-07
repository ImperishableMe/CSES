#include <bits/stdc++.h>
using namespace std;

#define L(x) (x)<<1
#define R(x) (x)<<1|1

using ll = long long int;

struct Node{
    ll f_cost = 0, r_cost = 0;
    Node(){}
    Node(ll fc, ll rc): f_cost(fc), r_cost(rc){}
};


int const N = 2e5 + 10;
Node t[4*N];
ll a[N];
ll const INF = 1e17;

Node const IDENTITY = Node(INF, INF);

Node merge(Node l, Node r, ll st, ll en){
    Node tmp;
    tmp.f_cost = min(l.f_cost, r.f_cost);
    tmp.r_cost = min(l.r_cost, r.r_cost);

    return tmp;
}

void build(int p, int l, int r){
    if (l == r) {
        t[p] = Node(a[l]-l, a[l] + l); return;
    }
    int mid = (l+r)/2;
    build(L(p), l, mid);
    build(R(p), mid+1, r);

    t[p] = merge(t[L(p)], t[R(p)], l, r);

    // cout << "(" << l << " ," << r << ") " << t[p].f_cost << " " << t[p].r_cost << endl;    
}

void update(int p, int l, int r, int ul, int ur, ll val){
    if (l > ur || r < ul) return;
    if (ul <= l && r <= ur) {
        t[p] = Node(val - l, val + l);
        return;
    }
    int mid = (l+r)/2;
    update(L(p), l, mid, ul, ur, val);
    update(R(p), mid+1, r, ul, ur, val);

    t[p] = merge(t[L(p)], t[R(p)], l, r);
}

Node Q(int p, int l, int r, int ql, int qr){
    if (l > qr || r < ql) return IDENTITY;
    if (ql <= l && r <= qr) return t[p];

    int mid = (l+r)/2;

    return merge(
        Q(L(p), l, mid, ql, qr),
        Q(R(p), mid+1, r, ql, qr), l, r
    );
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    while (q--){
        int t, l, r;
        cin >> t;

        if (t == 1){
            int k, x;
            cin >> k >> x;
            update(1, 1, n, k, k, x);
        }
        else {
            int k;
            cin >> k;
            ll c1 = Q(1, 1, n, 1, k).f_cost + k;
            ll c2 = Q(1, 1, n, k, n).r_cost - k;

            cout << min(c1, c2) << "\n";
        }
    }

    return 0;
}