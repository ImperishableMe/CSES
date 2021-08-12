#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;
using ll = long long int;
using PLL = pair<ll,ll>;
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

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	ll n, k;
	cin >> n >> k;

	vector<PLL> v(n);

	for (auto &[x, y] : v) cin >> x >> y;

	sort(all(v), [](PLL a, PLL b)->bool{
		return PLL(a.second, a.first) < PLL(b.second, b.first);
	});

	multiset<ll> ends;
	for (int i = 0; i < k; i++) ends.insert(0);
	int ans = 0;
	for (auto [x, y] : v) {
		assert(ends.size());
		auto it = ends.upper_bound(x);
		if (it == ends.begin()) continue;
		ll val = *(prev(it));
		ends.erase(prev(it));
		ends.insert(y);
		ans++;
	}
	cout << ans << endl;
	return 0;
}