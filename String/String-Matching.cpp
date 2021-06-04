/**
 * Uses hashing, and map
 * */
 
#include <bits/stdc++.h>
using namespace std;
 
 
#define F first
#define S second
using ull = unsigned long long int;
 
typedef long long int ll;
 
typedef pair < ll,ll > PLL;
 
ostream& operator<<(ostream & os, PLL h){
	return os << "( " << h.F << ", " << h.S << " )" << endl;
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
 
struct gpHash
{
    ll operator()(PLL h) const { return h.first*1000000000+h.second; } // return h.h1^1023240101 in case of single hashing
};
 
// gp_hash_table<PLL, int, gpHash>ma;
 
 
PLL operator+ (PLL a, ll x)     {return {a.F + x, a.S + x} ;}
PLL operator- (PLL a, ll x)     {return {a.F - x, a.S - x} ;}
PLL operator* (PLL a, ll x)     {return {a.F * x, a.S * x} ;}
PLL operator+(PLL x, PLL y)		{ return {x.F + y.F,x.S + y.S} ;}
PLL operator-(PLL x,PLL y) 		{ return {x.F - y.F, x.S - y.S} ;}
PLL operator*(PLL x,PLL y) 		{ return {x.F * y.F , x.S * y.S} ;}
PLL operator%(PLL x,PLL y) 		{ return {x.F % y.F, x.S % y.S} ;}
 
ll B = 31, M = 1e9 + 9;
ll MOD = 1e9 + 7;
int const N = 1e6 + 10;
ll p[N], H[N];
 
ll calc_hash(string &s){
	ll h = 0;
	for (auto x : s){
		h = (h*B + (x-'a'+1)) % M;
	}
	return h;
}
 
ll subStr(int l, int r){
	return (H[r] - p[r-l+1]*H[l-1]%M + M) % M;
}
 
void solve(){
	p[0] = 1;
	for (int i = 1; i < N; i++) p[i] = (p[i-1] * B) % M;

    string s, t;
	cin >> s >> t;
	int n = s.size();
	H[0] = 0;
	for (int i = 1; i <= n; i++){
		H[i] = (H[i-1] * B + (s[i-1] - 'a' + 1)) % M;
	}
    
    int ans = 0;
    ll p_h = calc_hash(t);
    for (int i = 1; i <= n; i++){
        if (i >= t.size() && subStr(i - t.size() + 1, i) == p_h) {
            ans++;
        }
    }
    cout << ans << "\n";
}
int main(){
 
	ios::sync_with_stdio(false); cin.tie(0);
	int t = 1;
	while (t--) solve();
	
	return 0;
}