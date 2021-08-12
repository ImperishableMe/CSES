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

using tp = tuple<int,int,int>;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<tp> ran(n);
	int i = 0;
	for (auto &[x, y, ind] : ran){
		cin >> x >> y;
		ind = i++;
	}
	ordered_set left, right;

	sort(all(ran), [](tp a, tp b)->bool{
		return get<0>(a) == get<0>(b)? get<1>(a) > get<1>(b) : get<0>(a) < get<0>(b);
	});
	vector<int> I_am_covered(n, 0), covered_by_me(n, 0);

	for (int i = 0; i < n; i++){
		auto [st, en, ind] = ran[i];
		I_am_covered[ind] = i - left.order_of_key({en, -1});
		left.insert({en,i});
	}

	for (int i = n-1; i >= 0; i--){
		auto [st, en, ind] = ran[i];
		covered_by_me[ind] = right.order_of_key({en, n+1});
		right.insert({en,i});
	}

	for (int i = 0; i < n; i++) cout << (covered_by_me[i] > 0) << " ";
	cout << endl;
	for (int i = 0; i < n; i++) cout << (I_am_covered[i] > 0) << " ";
	cout << endl;

	return 0;
}