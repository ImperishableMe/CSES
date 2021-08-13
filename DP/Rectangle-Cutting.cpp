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
	int r, c;
	cin >> r >> c;
	int const INF = 1e7;
	vector<vector<int>> dp(r+2, vector<int>(c+2, INF));
	dp[0][0] = 0;

	for (int i = 1; i <= r; i++){
		for (int j = 1; j <= c; j++){
			if (i == j) dp[i][j] = 0;
			else {
				for (int cr = 1; cr < i; cr++)
					dp[i][j] = min(dp[i][j], 1+dp[cr][j]+dp[i-cr][j]);
				for (int cc = 1; cc < j; cc++)
					dp[i][j] = min(dp[i][j], 1+dp[i][cc]+dp[i][j-cc]);
			}
		}
	}
	cout << dp[r][c] << endl;

	return 0;
}