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

ll const LIM = 4e18;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	ll n, t;
	cin >> n >> t;

	vector<ll> k(n);
	for (auto &x : k) cin >> x;

	auto can = [&k, &t](ll timer)->bool{
		ll tot = 0;
		for (auto x : k){
			tot += timer/x;
			if (tot >= t) return 1;
		}
		return tot >= t;
	};

	ll lo = 0, hi = LIM;
	while (lo < hi){
		ll mid = (lo+hi)/2;
		if (can(mid)) hi = mid;
		else lo = mid+1;
	}
	cout << lo << endl;


	return 0;
}