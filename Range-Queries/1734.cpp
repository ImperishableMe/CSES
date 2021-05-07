#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;

typedef long long int ll;

typedef pair < int,int > PII;
typedef pair < ll,ll > PLL;

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;
#define all(v) (v).begin(),(v).end()


int const N = 2e5 + 10;
vector<PII> R[N];

int main(){

	ios::sync_with_stdio(false); cin.tie(0);
    int n, q;
    cin >> n >> q;

    map<int,int> last;

    vector<int> v(n+1);

    for (int i = 1; i <= n; i++) cin >> v[i];

    for (int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        R[r].emplace_back(l, i);
    }

    ordered_set ost;
    vector<int> ans(q);

    for (int i = 1; i <= n; i++){
        if (last.count(v[i])){
            ost.erase(last[v[i]]);
        }
        ost.insert(i);
        last[v[i]] = i;

        for (auto [l, ind] : R[i]){
            ans[ind] = ost.size() - ost.order_of_key(l);
        }
    }

    for (auto x : ans) cout << x << "\n";

	return 0;
}
