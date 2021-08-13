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

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, x;
	cin >> n >> x;
	vector<PLL> book(n);
	
	for (int i = 0; i < n; i++) cin >> book[i].F;
	for (int i = 0; i < n; i++) cin >> book[i].S;


	vector<vector<ll>> dp(2, vector<ll> (x+1, 0));

	for (int i = 0; i < n; i++){
		auto [pr, pg] = book[i];
		for (int tot = x; tot >= 0; tot--){
			dp[i&1][tot] = dp[1-(i&1)][tot];
			if (tot >= pr){
				dp[i&1][tot] = max(dp[1-(i&1)][tot], pg + dp[1-(i&1)][tot - pr]);
			}
		}
		// cout << "node " << i << endl;
		// for (auto p : dp[i&1]) cout << p << " ";
		// cout << endl;
	}	
	cout << *max_element(all(dp[(n-1)&1])) << endl;
	
	return 0;
}