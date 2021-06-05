/**
 * Uses hashing, and map
 * */
 
#include <bits/stdc++.h>
using namespace std;
 
 
#define F first
#define S second
using ull = uint64_t;
 
typedef long long int ll;
 
 
#define MODTYPE ull
 
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
PLL operator%(PLL x,ll y) 		{ return {x.F % y, x.S % y} ;}
PLL operator+(PLL x, PLL y)		{ return {x.F + y.F,x.S + y.S} ;}
PLL operator-(PLL x,PLL y) 		{ return {x.F - y.F, x.S - y.S} ;}
PLL operator*(PLL x,PLL y) 		{ return {x.F * y.F , x.S * y.S} ;}
PLL operator%(PLL x,PLL y) 		{ return {x.F % y.F, x.S % y.S} ;}
 
MODTYPE B = 31;
MODTYPE M = mod;
MODTYPE ONE = 1;
MODTYPE ZERO = 0;
 
ll MOD = 1e9 + 7;
int const N = 2e6 + 10;
MODTYPE p[N], H[N];
 
MODTYPE calc_hash(string &s){
	MODTYPE h = ZERO;
	for (auto x : s){
		h = modsum(modmul(h,B), (x-'a'+1));// % M;
	}
	return h;
}
 
MODTYPE subStr(int l, int r){
	return modsum(modsum(H[r],M-modmul(p[r-l+1],H[l-1])), M);
}
 
void solve(){
	p[0] = ONE;
	for (int i = 1; i < N; i++) {
		p[i] = modmul(p[i-1],B) ;
	}
 
    string s;
	cin >> s;
	int n = s.size();

	s += s;
 
	H[0] = ZERO;
	for (int i = 1; i <= 2*n; i++){
		H[i] = modsum(modmul(H[i-1], B),(s[i-1] - 'a' + 1));
	}

	int ans = 1;
	// cout << s << endl;

	for (int i = 2; i <= n; i++){
		int match_len = 0;
		int lo = 0, hi = n;
		while (lo <= hi){
			int mid = (lo+hi+1)/2;
			if (subStr(ans, ans+mid-1) == subStr(i, i+mid-1)){
				lo = mid + 1;
				match_len = max(match_len, mid);
			}
			else hi = mid - 1;
		}
		// cout << "Current " << s.substr(ans-1, n) << " " << s.substr(i-1, n) << endl;
		// cout << i << "  " << match_len << endl;

		if (match_len != n){
			if (s[ans+match_len-1] > s[i+match_len-1]) {
				ans = i;
			}
		}
		// cout << "ans " << ans << endl;
	}
	cout << s.substr(ans-1, n) << "\n";
 
}
int main(){
 
	ios::sync_with_stdio(false); cin.tie(0);
	int t = 1;
	while (t--) solve();
	
	return 0;
}
