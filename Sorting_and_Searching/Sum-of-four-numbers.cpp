#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using PLL = pair<ll,ll>;
#define F first
#define S second
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

// use 
// ht<int, PLL> mp;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n, x;
	cin >> n >> x;

	vector<PLL> v(n);
	int cnt = 0;
	for (auto &[x,y] : v) cin >> x, y = cnt++;
	// sort(all(v));
	ht<ll, PLL> mp;

	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			ll val = x - v[i].first - v[j].first;
			auto ft = [v](int pos)->void{
				cout << v[pos].second + 1 << " ";
			};
			if (mp.find(val) != mp.end()) {
				ft(i);
				ft(j);
				ft(mp[val].first);
				ft(mp[val].second);
				cout << endl;
				return 0;
			}
		}
		for (int p = i-1; p >= 0; p--){
			mp[v[p].first + v[i].first] = {p, i};
		}
	}

	cout << "IMPOSSIBLE\n";
	
	return 0;
}