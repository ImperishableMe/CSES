#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using PLL = pair<ll,ll>;
#define all(v) (v).begin(), (v).end()


int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	ll n, x;
	cin >> n >> x;

	vector<ll> v(n);
	for (auto &x : v) cin >> x;

	ll ans = 0, r = -1, tot = 0;
	for (int l = 0; l < n; l++){
		while (r+1 < n && tot + v[r+1] <= x) r++, tot += v[r];
		if (r < n && tot == x) ans++;
		tot -= v[l];
	}
	cout << ans << endl;

	return 0;
}