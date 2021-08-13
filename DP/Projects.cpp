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

int const N = 2e5 + 10;
int n;
ll dp[N];
vector<tp> projs;

ll DP(int pos){
	if (pos >= n) return 0;
	ll &r = dp[pos];
	if (r != -1) return r;
	r = 0;
	r = DP(pos+1);
	auto [a, b, p] = projs[pos];
	int nxt = upper_bound(projs.begin()+pos+1, projs.end(), tuple(b, 1e18, 1e18)) - projs.begin();
	r = max(r, DP(nxt) + p);
	return r;
}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	memset(dp, -1, sizeof dp);

	projs.resize(n);

	for (auto &[a, b, p] : projs) cin >> a >> b >> p;

	sort(all(projs));
	cout << DP(0) << endl;
	return 0;
}