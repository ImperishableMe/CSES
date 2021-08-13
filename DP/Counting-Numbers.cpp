#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
using ll = long long int;
using PLL = pair<ll,ll>;
#define F first
#define S second
#define all(v) (v).begin(), (v).end()

typedef tree<PLL, null_type, less<PLL>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// find_by_order(k) --> returns iterator to the kth largest element counting from 0
// order_of_key(val) --> returns the number of items in a set that are strictly smaller than our item

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

struct chash { /// use most bits rather than just the lowest ones
	const uint64_t C = ll(2e18*acos((long double)-1))+71; // large odd number
	const int RANDOM = rng();
	ll operator()(ll x) const { /// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
		return __builtin_bswap64((x^RANDOM)*C); }
};

template<class K,class V> using ht = gp_hash_table<K,V,chash>;

ll const M = 1e9 + 7;

inline void modSum(ll &s, ll a){
	if (a >= M) a -= M;
	s += a;
	if (s >= M) s -= M;
}
using tp = tuple<ll,ll,ll>;

ll dp[20][20][3];


vector<int> digify(ll n){
	vector<int> digs;
	if (n == 0) return {0};
	while (n){
		digs.push_back(n%10);
		n /= 10;
	}
	return digs;
}

vector<int> dig;

ll DP(int pos, int last, bool isSm){
	if (pos < 0) return 1;
	ll &r = dp[pos][last][isSm];
	if (r != -1) return r;
	r = 0;
	if (isSm){
		for (int i = 0; i < 10; i++){
			if (i == last) continue;
			r += DP(pos-1, i, 1);
		}
	}
	else {
		for (int i = (last == 10); i <= dig[pos]; i++){
			if (i == last) continue;
			r += DP(pos-1, i, (dig[pos] > i));
		}
	}
	return r;
}

ll ans(ll num){
	dig = digify(num);
	memset(dp, -1, sizeof dp);
	return DP((int)dig.size()-1, 10, 0);
}

ll tot(ll num){
	if (num < 0) return 0;
	if (num == 0) return 1;
	ll r = ans(num) + 1; // 1 for 0
	for (ll cur = 9; cur < num; cur = cur*10+9){
		r += ans(cur);
	}
	return r;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	ll a, b;
	cin >> a >> b;
	// cout << ans(b) << " " << ans(a-1) << endl;
	cout << tot(b) - tot(a-1) << endl;
	return 0;
}