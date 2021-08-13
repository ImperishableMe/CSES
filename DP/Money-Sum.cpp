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

int const N = 100*1000 + 10;

bitset<N> dp;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<int> x(n);
	for (auto &v : x) cin >> v;

// bitset soln 
	dp.reset();
	dp[0] = 1;
	for (auto val : x) dp |= (dp << val);

	cout << dp.count() - 1 << endl;

	for (int i = 1; i < dp.size(); i++){
		if (dp[i]) cout << i << " ";
	}
	cout << endl;



// typical soln 	
	// vector<bool> can_make(100*1000+10, 0);
	// can_make[0] = 1;

	// for (auto val : x){
	// 	for (int i = can_make.size()-1; i >= 0; i--){
	// 		if(i>=val) can_make[i] = can_make[i] | can_make[i-val];
	// 	}
	// }
	// int ans = 0;
	// for (int i = 1; i < can_make.size(); i++) ans += can_make[i];
	// cout << ans << endl;
	// for (int i = 1; i < can_make.size(); i++) {
	// 	if (can_make[i]) cout << i << " ";
	// }
	// cout << endl;
	return 0;
}