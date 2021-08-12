#include <bits/stdc++.h>
using namespace std;
using ll = long long int;

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	int n;
	cin >> n;
	vector<ll> v(n);
	ll tot = 0;
	for (auto &x : v) cin >> x, tot += x;
	sort(v.begin(), v.end());
	if (v.back() * 2 > tot)	{
		cout << 2 * v.back() << "\n";
	}
	else cout << tot << "\n";
	return 0;
}