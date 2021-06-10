/**
 * Uses hashing, and map
 * */
 
#include <bits/stdc++.h>
using namespace std;
 
 
#define F first
#define S second
using ull = uint64_t;
 
typedef long long int ll;
 
 
#define MODTYPE int
 
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
MODTYPE M = 1e9 + 7;
MODTYPE ONE = 1;
MODTYPE ZERO = 0;
 
ll MOD = 1e9 + 9;
int const N = 1e6 + 10;
MODTYPE p[N], H[2][N];
 
MODTYPE calc_hash(string &s){
	MODTYPE h = ZERO;
	for (auto x : s){
		// h = modsum(modmul(h,B), (x-'a'+1));// % M;
	}
	return h;
}
 
MODTYPE subStr(int l, int r, int pos){
	MODTYPE val = (H[pos][r] - 1LL * p[r-l+1] * H[pos][l-1] + M) % M;
	if (val < 0) val += M;
	return val;
}
int n;
 
MODTYPE subRev(int l, int r){
	return subStr(n-r+1, n-l+1, 1);
}
 
void solve(){
	p[0] = ONE;
	for (int i = 1; i < N; i++) {
		p[i] = 1LL*p[i-1]*B % M ;
	}
 
    string s, rev;
	cin >> s;
	n = s.size();
	rev = s;
	reverse(rev.begin(), rev.end());
 
	H[0][0] = ZERO;
	for (int i = 1; i <= n; i++){
		H[0][i] = (1LL*H[0][i-1]*B + (s[i-1] - 'a' + 1)) % M;
	}
	H[1][0] = ZERO;
 
	for (int i = 1; i <= n; i++){
		H[1][i] = (1LL*H[1][i-1]*B + (rev[i-1] - 'a' + 1)) % M;
	}
 
	int ans = 1, len = 0;
 
	for (int i = n/2, cnt = 1; cnt <= n; i = (i+1)%n + 1, cnt++){
		int match_len = 0;
		int lo = len, hi = min(i-1, n-i);
		while (lo <= hi){
			int mid = (lo+hi+1)/2;
			MODTYPE m1 = subStr(i-mid,i-1,0);
			MODTYPE m2 =  subRev(i+1, i+mid);
 
			if (m1 == m2){
				match_len = max(match_len, mid);
				lo = mid + 1;
			}
			else hi = mid - 1;
		}
		if (match_len > len) {
			len = match_len;
			ans = i;
		}
	}
	// cout << s.substr(ans-len-1, 2*len + 1) << "\n";
	int ans_e = 0, len_e = 0;
 
	for (int i = (n/2), cnt = 1; cnt <= n; i = (i+1)%n + 1, cnt++){
		int match_len = 0;
		int lo = max(ans_e, len), hi = min(i, n-i);
		while (lo <= hi){
			int mid = (lo+hi+1)/2;
			MODTYPE m1 = subStr(i-mid+1,i,0);
			MODTYPE m2 =  subRev(i+1, i+mid);
 
			if (m1 == m2){
				match_len = max(match_len, mid);
				lo = mid + 1;
			}
			else hi = mid - 1;
		}
		if (match_len > len_e) {
			len_e = match_len;
			ans_e = i;
		}
	}
	// cout << len << endl;
	if (len_e * 2 > 2*len + 1){
		cout << s.substr(ans_e-len_e, 2*len_e) << "\n";
	}
	else {
		cout << s.substr(ans-len-1, 2*len + 1) << "\n";
	}
 
}
int main(){
 
	ios::sync_with_stdio(false); cin.tie(0);
	// clock_t s = clock();
 
	int t = 1;
	while (t--) solve();
	// cout << (1.0* clock() - s)/ CLOCKS_PER_SEC << endl;
	return 0;
}