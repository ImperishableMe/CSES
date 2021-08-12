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

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	ll n, a, b;
	cin >> n >> a >> b;

	vector<ll> v(n+1), pref(n+1, 0);
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
		pref[i] = pref[i-1] + v[i];
	}

	deque<PLL> dq;
	dq.push_back({0, 0});
	ll ans = -1e18;

	for (int i = a; i <= n; i++){
		while (dq.size() && dq.front().S < i-b) dq.pop_front();
		
		while (dq.size() && dq.back().F >= pref[i-a]) dq.pop_back();
		dq.push_back({pref[i-a], i-a});

		// cout << "node " << i << endl;
		// for (auto [x, y]: dq) cout << x << " " << y << endl;

		assert(dq.size());
		ans = max(ans, pref[i] - dq.front().F);
	}
	cout << ans << endl;
	
	return 0;
}