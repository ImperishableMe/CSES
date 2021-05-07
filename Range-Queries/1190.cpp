#include <bits/stdc++.h>
using namespace std;

#define L(x) (x)<<1
#define R(x) (x)<<1|1

using ll = long long int;

struct Node{
    ll maxSub, pref, suf, sum;
    Node(){
        maxSub = pref = suf = sum = 0;
    }
    Node(ll sum, ll m, ll p, ll s):maxSub(m), pref(p), suf(s), sum(sum){}
};


int const N = 2e5 + 10;
Node t[4*N];
ll a[N];

Node const IDENTITY = Node(0,0,0,0);

Node merge(Node l, Node r){
    Node tmp;
    tmp.pref = max(l.pref, l.sum + r.pref);
    tmp.suf = max(r.suf, r.sum + l.suf);
    tmp.sum = l.sum + r.sum;
    tmp.maxSub = max(0LL, max(l.maxSub, max(
       r.maxSub, l.suf + r.pref 
    )));
    return tmp;
}

void build(int p, int l, int r){
    if (l == r) {
        t[p] = Node(a[l], a[l], a[l], a[l]); return;
    }
    int mid = (l+r)/2;
    build(L(p), l, mid);
    build(R(p), mid+1, r);

    t[p] = merge(t[L(p)], t[R(p)]);
}

void update(int p, int l, int r, int ul, int ur, ll val){
    if (l > ur || r < ul) return;
    if (ul <= l && r <= ur) {
        t[p] = Node(val, val, val, val);
        return;
    }
    int mid = (l+r)/2;
    update(L(p), l, mid, ul, ur, val);
    update(R(p), mid+1, r, ul, ur, val);

    t[p] = merge(t[L(p)], t[R(p)]);
}

Node Q(int p, int l, int r, int ql, int qr){
    if (l > qr || r < ql) return IDENTITY;
    if (ql <= l && r <= qr) return t[p];

    int mid = (l+r)/2;

    return merge(
        Q(L(p), l, mid, ql, qr),
        Q(R(p), mid+1, r, ql, qr)
    );
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    while (q--){
        int k, x;
        cin >> k >> x;
        update(1, 1, n, k, k, x);
        cout << Q(1, 1, n, 1, n).maxSub << "\n";
    }
    return 0;
}