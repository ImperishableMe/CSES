#include <bits/stdc++.h>
using namespace std;
 
#define L(x) (x)<<1
#define R(x) (x)<<1|1
 
using ll = long long int;
 
ll const IDENTITY = 0;
 
int const N = 2e5 + 10;
ll t[4*N], lz[4*N], tlz[4*N];
ll a[N];
 
ll merge(ll l, ll r){
    return l + r;
}
 
ll cnt(ll n){
    return n * (n+1)/2;
}
 
void push(int p, int l, int r){
    if (lz[p] or tlz[p]){
        t[p] += lz[p] * (r - l + 1) + tlz[p] * cnt(r - l + 1);
        if (l != r){
            int mid = (l+r)/2;
            
            lz[L(p)] += lz[p];
            lz[R(p)] += tlz[p] * (mid-l+1) + lz[p];
            tlz[L(p)] += tlz[p];
            tlz[R(p)] += tlz[p];
            
        }
    }
    lz[p] = 0;
    tlz[p] = 0;
}
 
void build(int p, int l, int r){
    if (l == r) {
        t[p] = a[l]; return;
    }
    int mid = (l+r)/2;
    build(L(p), l, mid);
    build(R(p), mid+1, r);
 
    t[p] = merge(t[L(p)], t[R(p)]);
}
 
 
void update(int p, int l, int r, int ul, int ur, ll val){
    push(p, l, r);

    if (l > ur || r < ul) return;
 
    if (ul <= l && r <= ur) {
        ll len = r - l + 1;
 
        t[p] += len*(len+1)/2  + len*(l-ul);
 
        if (l != r){
            int mid = (l+r)/2;
            
            lz[L(p)] += (l-ul);
            lz[R(p)] += (mid+1-ul);
            tlz[L(p)] += 1;
            tlz[R(p)] += 1;
        }
        return;
    }
 
    int mid = (l+r)/2;
    update(L(p), l, mid, ul, ur, val);
    update(R(p), mid+1, r, ul, ur, val);
 
    t[p] = merge(t[L(p)], t[R(p)]);
}
 
ll Q(int p, int l, int r, int ql, int qr){
    push(p, l, r);

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
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1){
            update(1, 1, n, l, r, 0);
        }
        else {
            cout << Q(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}