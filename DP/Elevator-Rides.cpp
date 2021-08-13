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

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	ll n, x;
	cin >> n >> x;
	vector<ll> w(n);
	for (auto &c : w) cin >>c;

	vector<PLL> dp(1<<n);
	dp[0] = {1, 0};
	for (int s = 1; s < (1<<n); s++){
		dp[s] = {n+1, 0};
		for (int cur = 0; cur < n; cur++){
			if (!(s & (1<<cur))) continue;
			auto [ride, so_far] = dp[s^(1<<cur)];
			if (so_far + w[cur] <= x) {
				so_far += w[cur];
			}
			else {
				ride++;
				so_far = w[cur];
			}
			dp[s] = min(dp[s], {ride, so_far});
		}
	}
	cout << dp[(1<<n)-1].first << endl;

	return 0;
}