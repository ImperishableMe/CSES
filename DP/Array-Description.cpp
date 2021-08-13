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
int const N = 1e5 + 10;
int n, m;
int v[N];
ll dp[N][103];

// recursive version (not called)
ll DP(int pos, int val){
	if (pos > n) return 1;
	if (val <= 0 || val > m) return 0;
	ll &r = dp[pos][val];
	if (r != -1) return r;
	r = 0;
	if (v[pos]){
		if (abs(val-v[pos]) > 1) return r = 0;
		modSum(r, DP(pos+1, v[pos]));
	}
	else {
		if (val+1 <= m) modSum(r, DP(pos+1, val+1));
		modSum(r, DP(pos+1, val));
		if (val-1 >= 1) modSum(r, DP(pos+1, val-1));
	}
	return r;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> v[i];

	for (int i = 1; i <= n; i++){
		if (i == 1){
			if (v[i]) dp[i][v[i]] = 1;
			else {
				for (int j = 1; j <= m; j++) dp[i][j] = 1;
			}
			continue;
		}
		for (int j = 1; j <= m; j++){
			if (v[i] && v[i] != j) 
				dp[i][j] = 0;
			else {
				ll add = dp[i-1][j-1] + dp[i-1][j] + dp[i-1][j+1];
				add %= M;
				modSum(dp[i][j], add);
			}
		}
	}

	ll ans = 0;
	for (int i = 1; i <= m; i++) modSum(ans, dp[n][i]);
	cout << ans << endl;

	return 0;
}