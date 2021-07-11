#include <bits/stdc++.h>
 
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// to generate a uniform random integer over a range (l,r), use 
// int x = uniform_int_distribution<int>(l,r)(rng);

#define F first
#define S second
using ull = unsigned long long int;
typedef long long int ll;
using PLL = pair<ll,ll>; 

#define MODTYPE PLL
 
typedef pair < ll,ll > PLL;
 
ostream& operator<<(ostream & os, PLL h){
	return os << "( " << h.F << ", " << h.S << " )";
}
 
constexpr uint64_t mod = (1ull<<61) - 1;
uint64_t modmul(uint64_t a, uint64_t b){
    uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
    uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    uint64_t ret = (l&mod) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret>>61);
    ret = (ret & mod) + (ret>>61);
    return ret-1;
}
uint64_t modsum(uint64_t a, uint64_t b){
    ull x = a+b;
    if(a+b >= mod) x -= mod;
    return x;
}
 
 
PLL operator+ (PLL a, ll x)     {return {a.F + x, a.S + x} ;}
PLL operator- (PLL a, ll x)     {return {a.F - x, a.S - x} ;}
PLL operator* (PLL a, ll x)     {return {a.F * x, a.S * x} ;}
PLL operator%(PLL x,ll y) 		{ return {x.F % y, x.S % y} ;}
PLL operator+(PLL x, PLL y)		{ return {x.F + y.F,x.S + y.S} ;}
PLL operator-(PLL x,PLL y) 		{ return {x.F - y.F, x.S - y.S} ;}
PLL operator*(PLL x,PLL y) 		{ return {x.F * y.F , x.S * y.S} ;}
PLL operator%(PLL x,PLL y) 		{ return {x.F % y.F, x.S % y.S} ;}
 
MODTYPE B = {31, 37};
MODTYPE M = {1e9 + 9, 1e9 + 7};
MODTYPE ONE = {1,1};
MODTYPE ZERO = {0,0};

ll MOD = 1e9 + 7;
int const N = 2e5 + 10;
MODTYPE p[N], H[N];
 
#define L(x) (x)<<1
#define R(x) (x)<<1|1


struct node {
	MODTYPE shoja, ulta;
	int has = 0;
	node(MODTYPE l, MODTYPE r, int h):shoja(l), ulta(r), has(h){}
	node(){}
	bool operator==(node& rhs){
		return shoja == rhs.shoja && ulta == rhs.ulta;
	}
	bool operator!=(node& rhs){
		return !(*this == rhs);
	}
};
node const IDENTITY = node({0,0}, {0,0},0);

node t[4*N];
ll a[N];
string s;

node merge(node ln, node rn, int l, int r){
	int mid = (l+r)/2;
	node cur;
	cur.shoja = (ln.shoja * p[rn.has] + rn.shoja) % M;
	cur.ulta = (ln.ulta + rn.ulta * p[ln.has]) % M;
	cur.has = ln.has + rn.has;
	return cur;
}

void build(int p, int l, int r){
    if (l == r) {
        t[p].shoja = {(s[l-1]-'a'+1), s[l-1]-'a'+1}; 
		t[p].ulta = t[p].shoja;
		t[p].has = 1;
		return;
    }
    int mid = (l+r)/2;
    build(L(p), l, mid);
    build(R(p), mid+1, r);

    t[p] = merge(t[L(p)], t[R(p)], l, r);
}

void update(int p, int l, int r, int ul, int ur, int val, int has){
    if (l > ur || r < ul) return;
    if (ul <= l && r <= ur) {
        t[p].shoja = {val, val}; 
		t[p].ulta = t[p].shoja;
		t[p].has = has;
        return;
    }
    int mid = (l+r)/2;
    update(L(p), l, mid, ul, ur, val, has);
    update(R(p), mid+1, r, ul, ur, val, has);

    t[p] = merge(t[L(p)], t[R(p)], l, r);
}

pair<node,int> Q(int pp, int l, int r, int ql, int qr){
    if (l > qr || r < ql) return {IDENTITY,0};
    if (ql <= l && r <= qr) return {t[pp], t[pp].has};

    int mid = (l+r)/2;

    auto [ln, lc] = Q(L(pp), l, mid, ql, qr);
    auto [rn, rc] = Q(R(pp), mid+1, r, ql, qr);

	node cur;
	int cnt = lc + rc;
	cur.shoja = (ln.shoja * p[rc] + rn.shoja) % M;
	cur.ulta = (ln.ulta + rn.ulta * p[lc]) % M;
	
	return {cur, cnt};
}

void solve(){
	ordered_set ost;

	p[0] = ONE;
	for (int i = 1; i < N; i++) {
		p[i] = (p[i-1] * B) % M;
	}

	cin >> s;
	int n, m;
	cin >> m;

	n = s.size();

	for (int i = 1; i <= n; i++) ost.insert(i);

	build(1, 1, n);

	while(m--){
		char ch;
		cin >> ch;
		if (ch == 'U'){
			int k;
			char ch;
			cin >> k >> ch;
			k = *ost.find_by_order(k-1);
			update(1, 1, n, k, k, ch - 'a' + 1, 1);
		}
		else if(ch == 'C'){
			int a, b;
			cin >> a >> b;
			a = *ost.find_by_order(a-1);
			b = *ost.find_by_order(b-1);
			auto [ret, cnt] = Q(1, 1, n, a, b);
			cout << ((ret.shoja == ret.ulta)? "Yes!": "No!") << "\n";
		}
		else {
			int ind;
			cin >> ind;
			ind = *ost.find_by_order(ind-1);
			update(1, 1, n, ind, ind, 0, 0);
			ost.erase(ind);
		}
	}
}

int main(){
 
	ios::sync_with_stdio(false); cin.tie(0);
	int t = 1;
	while (t--) solve();
	
	return 0;
}