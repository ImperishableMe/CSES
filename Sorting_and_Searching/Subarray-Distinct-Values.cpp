#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using PLL = pair<ll,ll>;
#define all(v) (v).begin(), (v).end()

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
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

	vector<ll> v(n);
	for (auto &x : v) cin >> x;

	ht<ll, int> cnt;
	ll distinct = 0;

	auto add = [&distinct, &cnt](ll val)->void{
		cnt[val]++;
		if (cnt[val] == 1) distinct++;
	};

	auto remove = [&distinct, &cnt](ll val)->void{
		cnt[val]--;
		if (cnt[val] == 0) distinct--;
	};

	int l = 0;
	ll ans = 0;
	for (int r = 0; r < n; r++){
		add(v[r]);
		while (l <= r && distinct > k) remove(v[l++]);
		assert(l<=r);
		ans += (r - l + 1);
	}
	cout << ans << endl;

	return 0;
}