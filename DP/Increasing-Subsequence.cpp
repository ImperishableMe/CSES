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

#define L(x) (x) << 1
#define R(x) (x) << 1 | 1
struct Node
{ // change
	ll val;
	Node() : val(0) {}
	Node(ll v) : val(v) {}
	bool operator==(const Node &node) const { return val == node.val; }
};
const Node QUERY_IDENTITY(0); // change
const Node LAZY_IDENTITY(0);  // change
int const N = 2e5 + 10;
Node t[4 * N];
ll a[N];
Node lazy[4 * N];
Node merge(const Node &a, const Node &b) { return Node(max(a.val ,b.val)); } // change
/**
* Given the lazy in the node, and a new operation,
* update the lazy value.
**/
void assignLazy(int p, Node op) { lazy[p].val += op.val; } // change
/**
* Given the lazy in for a node, calculate its value,
* and push the lazy down to the childs
**/
void push(int p, int l, int r)
{ // change
	if (!(lazy[p] == LAZY_IDENTITY))
	{
		auto last = lazy[p];
		if (l != r)
		{
			for (auto ch : {L(p), R(p)})
			{
				assignLazy(ch, last);
			}
		}
		t[p].val += (r - l + 1) * last.val;
	}
	lazy[p] = LAZY_IDENTITY;
}
void build(int p, int l, int r)
{
	if (l == r)
	{
		t[p] = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build(L(p), l, mid);
	build(R(p), mid + 1, r);
	t[p] = merge(t[L(p)], t[R(p)]);
}
void update(int p, int l, int r, int ul, int ur, Node op)
{
	push(p, l, r); // The order matters
	if (l > ur || r < ul)
		return;
	if (ul <= l && r <= ur)
	{
		assignLazy(p, op);
		push(p, l, r);
		return;
	}
	int mid = (l + r) / 2;
	update(L(p), l, mid, ul, ur, op);
	update(R(p), mid + 1, r, ul, ur, op);
	t[p] = merge(t[L(p)], t[R(p)]);
}
Node query(int p, int l, int r, int ql, int qr)
{
	push(p, l, r); // The order matters
	if (l > qr || r < ql)
		return QUERY_IDENTITY;
	if (ql <= l && r <= qr)
		return t[p];
	int mid = (l + r) / 2;
	return merge(query(L(p), l, mid, ql, qr), query(R(p), mid + 1, r, ql, qr));
}

int main(){

	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<PLL> v(n);

	for (int i = 0; i < n; i++) {
		cin >> v[i].F;
		v[i].S = i+1;
	}
	vector<int> lis(n+1, 0);

	sort(all(v), [](PLL a, PLL b)->bool{
		return (a.first == b.first)?a.S > b.S: a.F < b.F;
	});

	for (auto [val, ind] : v){
		// cout << val << " " << ind << endl;
		int mx = query(1, 1, n, 1, ind).val;
		lis[ind] = 1 + mx;
		update(1, 1, n, ind, ind, lis[ind]);
	}

	cout << *max_element(all(lis)) << endl;
	return 0;
}