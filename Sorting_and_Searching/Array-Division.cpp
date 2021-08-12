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

	auto can = [&v, &k](ll sum)->bool{
		ll cnt = 1, so_far = 0;
		for (auto x : v){
			if(x > sum) return 0;
			if (so_far + x > sum) cnt++, so_far = x;
			else so_far += x;
		}
		return cnt <= k;
	};
	ll ans = 1e18;
	ll lo = 0, hi = ans;

	while(lo <= hi){
		ll mid = (lo+hi+1)/2;
		if (can(mid)) ans = min(ans, mid), hi = mid-1;
		else lo = mid+1; 
	}

	cout << ans << "\n";

	return 0;
}