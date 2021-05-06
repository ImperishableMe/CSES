#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;

typedef long long int ll;
using PII = pair<int,int>;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main(){

	ios::sync_with_stdio(false); cin.tie(0);
	int n;
	cin >> n;
	vector<int> v(n);
	ordered_set ost;

	for (int i = 0; i < n; i++){
		cin >> v[i];
		ost.insert(i);
	}

	for (int i = 0; i < n; i++){
		int p;
		cin >> p;
		auto val = *ost.find_by_order(p-1);
		ost.erase(val);
		cout << v[val] << " ";
	}	
	cout << "\n";
	return 0;
}
