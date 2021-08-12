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
	vector<tp> g(n);
	int cnt = 1;
	for (auto &[x, y, z] : g) cin >> x >> y, z = cnt++;

	sort(all(g), [](tp a, tp b) {
		return make_pair(get<0>(a), get<1>(a) ) < make_pair(get<0>(b), get<1>(b));
	});

	priority_queue<PLL, vector<PLL>, greater<PLL>> pq;	
	vector<int> ans(n+1, -1);

	pq.push({0,1});
	for (auto [st, en, ind] : g){
		assert(pq.size());
		if (pq.top().F >= st){
			pq.push({en, pq.size()+1});
		    ans[ind] = pq.size();
		}
		else {
			ans[ind] = pq.top().S;
			pq.pop();
			pq.push({en, ans[ind]});
		}
	}
	cout << *max_element(ans.begin()+1, ans.end()) << endl;

	for (int i = 1; i <= n; i++){
		assert(ans[i] >= 0);
		cout << ans[i] << " \n"[i==n];
	}
	
	return 0;
}