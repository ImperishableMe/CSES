#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;

typedef long long int ll;
using PII = pair<int,int>;

typedef tree<
PII,
null_type,
less<PII>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main(){

	ios::sync_with_stdio(false); cin.tie(0);
	int n, q;
	cin >> n >> q;

	vector<int> p(n+1);
	ordered_set ost;

	for (int i = 1; i <= n; i++) cin >> p[i], ost.insert({p[i], i});

	while (q--){
		char type;
		int x, y;
		cin >> type >> x >> y;

		if (type == '!'){
			auto el = ost.find({p[x], x});
			ost.erase(el);
			p[x] = y;
			ost.insert({p[x], x});
		}
		else {
			cout << ost.order_of_key({y, n+1}) - ost.order_of_key({x, 0}) << '\n';
		}
	}

	return 0;
}
