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
	ll n, x;
	cin >> n;

	vector<ll> v(n);
	for (auto &x : v) cin >> x;

	vector<ll> cnt(n, 0);
	ll tot = 0, ans = 0;
	cnt[0] = 1;
	for (int i = 0; i < n; i++){
		tot += (v[i]%n + n) % n;
		tot %= n;
		ans += cnt[tot];
		cnt[tot]++;
	}
	cout << ans << endl;

	return 0;
}