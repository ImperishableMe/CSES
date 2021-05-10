#include <bits/stdc++.h>
using namespace std;

#define L(x) (x)<<1
#define R(x) (x)<<1|1

using ll = long long int;
using PLL = pair<ll,ll>;

ll const IDENTITY = 0;

int const N = 2e5 + 10;
ll t[4*N];
ll a[N];

ll merge(ll l, ll r){
    return l + r;
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

ll Query(int p, int l, int r, int ql, int qr){
    if (ql > qr) return 0;
    if (l > qr || r < ql) return IDENTITY;
    if (ql <= l && r <= qr) return t[p];

    int mid = (l+r)/2;

    return merge(
        Query(L(p), l, mid, ql, qr),
        Query(R(p), mid+1, r, ql, qr)
    );
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<ll> pref(n+2, 0);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i-1] + a[i];
    }
    vector<vector<PLL>> Q(n+1, vector<PLL>());
    
    for (int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        Q[l].emplace_back(r, i);
    }
    a[n+1] = 1e17;

    deque<int> stk = {n+1};
    vector<ll> contrib(n+1, 0);
    vector<ll> ans(q);

    for (int l = n; l >= 1; l--){

        while(stk.size() && a[l] >= a[stk.front()]){
            int ind = stk.front();
            update(1, 1, n, ind, ind, 0);
            stk.pop_front();
        }
        contrib[l] = 1LL * (stk.front() - l) * a[l] - (pref[stk.front()-1] 
            - pref[l-1]);

        update(1, 1, n, l, l, contrib[l]);

        // cout << "For ind " << l << " contrib " << contrib[l] <<  endl;

        // for (auto x : stk) cout << x << " ";
        // cout << endl;



        stk.push_front(l);

        for (auto [r, ind]: Q[l]){
            int pos = upper_bound(stk.begin(), stk.end(), r) - stk.begin() - 1;

            ans[ind] = Query(1, 1, n, l, stk[pos] - 1) + (
                (r - stk[pos]) * a[stk[pos]] - (pref[r] - pref[stk[pos]])
            );
        }
    }


    for (auto x : ans) cout << x << "\n";

    return 0;
}